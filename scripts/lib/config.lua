--[[---------------------------------------------------------------------------
Functions for saving/loading config data

This module is a lua script (@{config.lua}), you need to explicitly load it
with `require('config')`

@module config
]]
config = {}
config.configs = {}
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

local function insertMenu(cfg,m)
  local tmp = {}
  -- build new table
  tmp.menu = m

  if m.submenu == nil then
    -- Single menu entry. Save as a table with a single entry
    tmp[m.name] = m.value
  else
    for k,v in pairs(m.submenu) do
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

-- TODO: Refactor function body
local function recursiveCopy(o,m,cfg,s)
  local tmp = {}
  -- Copy value
  if type(o) == "number" or type(o) == "string" then
    if m ~= nil then
      if cfg[s] ~= nil then
        cfg[s][m.name] = m.value
      else
        cfg[m.name] = m.value
      end
    else
      cfg = o
    end
  -- Recurse over table
  elseif type(o) == "table" then
    if m == nil then print("MENU NIL\n")
    else
      for s,c in pairs(o) do
        local tmp = {}
        if m.submenu ~= nil then
          recursiveCopy(c,m.submenu[s],cfg,m.name)
        else
          -- Single menu entry
          recursiveCopy(m.value,m,cfg,nil)
        end
      end
    end
  else
    -- userdata
    cfg = o
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
      cfg.data[m.name].menu = m
      recursiveLoad(m,cfg.data[m.name])
    end

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
    -- k -> A table representing a menu entry or a single entry of a simple config
    if type(self.data[k]) == "table" then
      local menu = self.data[k].menu
      -- Copy menu and save values into .cfg
      recursiveCopy(v,menu,self.data[k],nil)
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
    config.serialize(f,self.data,1)
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
            f:write(string.rep("\t", lvl))
            f:write("[")
            config.serialize(f,k,lvl+1)
            f:write("] = ")
            config.serialize(f,v,lvl+1)
            f:write(",\n")
          end
        end
        -- Indent closing bracket
        f:write(string.rep("\t", lvl-1))
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
