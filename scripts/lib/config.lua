--[[---------------------------------------------------------------------------
Functions for saving/loading config data

This module is a lua script (@{config.lua}), you need to explicitly load it
with `require('config')`

@module config
]]
config = {}
config.configs = {}
config.menus = {}
config.__index = config

function config.findConfig(fileName)
  if fileName == nil then return nil end
  -- Iterate through configs
  for k,v in pairs(config.configs) do
    if v.filename == fileName then
      return v
    end
  end
  return nil
end

-- Function used to add the menu to config.configs[script_name]
-- Fill the config by replicating Menu's structure
local function insertMenu(cfg,m)
  local tmp

  if m.submenu == nil then
    -- Single menu entry. Save directly as a key value pair
    tmp = m.value
  else
    -- Menu with more than an entry. Save as a table
    tmp = {}
    for k,v in pairs(m.submenu) do
      -- build the new table
      if v.submenu ~= nil then
        -- Recurse into submenu
        tmp[k] = {}
        insertMenu(tmp,v)
      else
        tmp[k] = v.value
      end
    end
  end

  -- Add new table in menus array
  cfg[m.name] = tmp
end

-- Function used to update config in memory with the current menus values
-- Due to the need of passing parameters as arguments, the function is augmented with prev(reference to table) and key(entry name)
local function recursiveCopy(obj,menu,prev,key)
  if obj == nil or menu == nil then return end

  if type(obj) == "number" or type(obj) == "string" or type(obj) == "boolean" then
    prev[key] = menu.value
  elseif type(obj) == "table" then
    -- Recursive Step for each entry of the table
    for k,v in pairs(obj) do
      if menu.submenu == nil then
        -- Should not be reachable. Keep print just in case of conflicts with any future changes
        print("ERROR: menu.submenu is nil")
        return
      end
      -- use obj/k to pass the table by reference
      local m = menu.submenu[k]
      recursiveCopy(v,m,obj,k)
    end
  else
    -- Userdata and others
    prev[key] = menu.value
  end

end

-- Load config from file if exists, otherwise create a new table in memory
local create_internal = function(default,thisfile)
  local filename = string.format("%s%s.lcf", dryos.config_dir.path,thisfile)
  local cfg = config.findConfig(filename)

  if cfg == nil then
    -- Create a config from scratch
    cfg = {}
    cfg.filename = filename
    cfg.default = default -- TODO: Replicate .data's structure
    cfg.data = {}
    -- check for existing .cfg to load
    setmetatable(cfg,config)
    -- load previus config from file if available
    cfg.data = cfg:load()
    -- add to data structure
    table.insert(config.configs,cfg)
  end

  return cfg
end

local function recursiveLoad(m,cfg)
  if m.submenu == nil then
    if type(cfg) ~= "table" then
      -- Menu's entry. Copy value
      m.value = cfg
    else
      -- Single menu entry
      m.value = cfg[m.name]
    end
  else
    -- This menu has submenu. Recurse inside
    for k,v in pairs(m.submenu) do
      recursiveLoad(m.submenu[k],cfg[k])
    end
  end

end

--[[---------------------------------------------------------------------------
Create a new config instance, filename will be determined automagically
@param default the default data values
@function create
]]
function config.create(default)
  local short_name = string.match(debug.getinfo(2,"S").short_src,"/([^/%.]+)%.[^/%.]+$")
  local cfg = create_internal(default,short_name)

  -- Append config data
  for k,v in pairs(default) do
    cfg.default[k] = v
    cfg.data[k] = v
  end

  --  cfg.default = default -- TODO: Replicate .data's structure

  return cfg
end

--[[---------------------------------------------------------------------------
@type config
]]

--[[---------------------------------------------------------------------------
Get/Set the data to store to configuration
@field data
]]

--[[---------------------------------------------------------------------------
Create a new config instance from a menu structure, filename will be determined
automagically
@param m the menu to create a config for
@function create_from_menu
]]
function config.create_from_menu(m)
    assert(m ~= nil, "Can't create Config from Menu. Nil argument")

    local default = {}
    --default values are simply the menu's default values
    insertMenu(default,m)

    local short_name = string.match(debug.getinfo(2,"S").short_src,"/([^/%.]+)%.[^/%.]+$")
    local cfg = create_internal(default,short_name)

    if cfg.data[m.name] == nil then
      -- Create a config for menu from scratch
      insertMenu(cfg.data,m)
    else
      -- Already present in config.configs, load values to menu from config
      -- This appen when data is loaded from config after first call to create_internal
      recursiveLoad(m,cfg.data[m.name])
    end
    -- Save menu pointer to data structure. Used when saving config back to file
    config.menus[m.name] = m

    --    cfg.default = default -- TODO: Replicate .data's structure

    return cfg.data[m.name]
end

--[[---------------------------------------------------------------------------
Load the config data from file (by executing the file)
@function load
]]
function config:load()
    local status,result = pcall(dofile,self.filename)
    if status and result ~= nil then
        return result
    else
        print(result)
        return self.default
    end
end

--[[---------------------------------------------------------------------------
Called right before config data is saved to file, override this function to
update your config.data when the config is being saved
@function saving
]]
function config:saving()
  -- Copy values of each menu
  for k,v in pairs(self.data) do
    -- v/self.data[k] -> A table representing a menu entry or a single entry of a simple config
    local menu = config.menus[k]
    if type(self.data[k]) == "table" then
      -- It's a menu with more than one entry or a complex config field (table)
      if menu ~= nil then
        -- Copy menu and save values into .cfg
        recursiveCopy(v,menu,nil,nil)
      else
        -- Just a Placeholder: A config entry expressed as table. No need to do anything
        print("Saving - Table case - Config Table")
      end
    else
      -- It's a menu with single entry or a simple config field
      -- Handle only menu case
      if menu ~= nil then
        self.data[k] = menu.value
      else
        -- Just a Placeholder: A config entry expressed as simple value (not a talbe). No need to do anything
      end
    end
  end
end

--[[---------------------------------------------------------------------------
Manually save the config data to file (data is saved automatically when the
ML backend does it's config saving, so calling this function is unecessary
unless you want to do a manual save).
Whatever is in the 'data' field of this instance is saved. Only numbers,
strings and tables can be saved (no functions, threads or userdata)
@function save
]]
function config:save()
    local f = io.open(self.filename,"w")
    assert(f ~= nil, "Could not save config: "..self.filename)
    -- Serialize data into a loadable format
    f:write("return ")
    config.serialize(f,self.data,0)
    f:close()
end

--private
function config.serialize(f,o,lvl)
    if type(o) == "number" or type(o) == "boolean" then
        f:write(tostring(o))
    elseif type(o) == "string" then
        f:write(string.format("%q", o))
    elseif type(o) == "table" then
        f:write("{\n")
        for k,v in pairs(o) do
          if k ~= "menu" then
            -- Indent starting line
            f:write(string.rep("\t", lvl+1).."[")
            config.serialize(f,k,lvl+1)
            f:write("] = ")
            config.serialize(f,v,lvl+1)
            f:write(",\n")
          end
        end
        -- Indent closing bracket
        f:write(string.rep("\t", lvl))
        f:write("}")
    else
        --something we don't know how to serialize, just skip it
    end
end

-- Event config_save
if event.config_save == nil then
    event.config_save = function(unused)
        for i,v in ipairs(config.configs) do
           v:saving()
           v:save()
        end
    end
end

return config
