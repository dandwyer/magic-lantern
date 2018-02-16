-- Manual Lens Information
-- Supplies lens information for manual lenses
-- Whenever there is a non-chipped lens detected or a manual lens with AF Confirm Chip, we prompt the user to select the attached manual lens from a list

require("ui")
require("config")
require("xmp")

lenses =
{
--  The following is for testing purposes. Comment out the following lines then either uncomment only the lenses
--  that you want to use from the list or add your own lenses. Tip: Put your most used lenses at the top of the list.
--  Attributes to use:
--  name            -> Name to be showed in Lens Info and in metadata
--  focal_length    -> Current focal length to be saved in metadata (Zoom Lenses: Default value to be used after selecting lens)
--  manual_aperture -> Max Aperture of the Lens
--  focal_min       -> min Focal Length (optional for prime lenses)
--  focal_max       -> max Focal Length (optional for prime lenses)
--  serial          -> Lens Serial Number (optional)
--  f_values        -> Available f-stop for selected lens (optional)

{ name = "My Lens", focal_length = 50, serial = 123456789 },
{ name = "My Other Lens", focal_length = 25, manual_aperture = 2.8, f_values = {"2.8","4","5.6","8"} },
{ name = "My Zoom Lens", focal_length = 25, manual_aperture = 4, focal_length = 105, focal_min = 70, focal_max = 200 },
{ name = "Yashica ML 50mm f1.9", focal_length = 50, serial = 123, manual_aperture = 5 },
{ name = "Portrait 85mm", focal_length = 85, manual_aperture = 2 },
{ name = "Portrait 105mm", focal_length = 105, focal_min = 105, focal_max = 105, manual_aperture = 8 },
{ name = "Pentax SMC 80-200mm f4,5", focal_length = 200, manual_aperture = 4.5, serial = 123456789 },
{ name = "Pentax SMC 80-200mm f4,5 with focal length min-max", focal_length = 200, focal_min = 80, focal_max = 200, manual_aperture = 4.5, serial = 123456789 },
{ name = "Portrait 125mm 2.8", focal_length = 125, manual_aperture = 2.8 },
{ name = "Portrait 200mm 5.6", focal_length = 200, focal_min = 200, focal_max = 200, manual_aperture = 5.6 },
{ name = "Portrait 125mm 1.4", focal_length = 125, manual_aperture = 1.4 },
{ name = "Carl Zeiss Vario-Sonnar T* 100-300 mm f/ 4.5-5.6 C/Y", focal_length = 150, focal_min = 100, focal_max = 300, manual_aperture = 4.5, f_values = {"4.5","8","11","16","22","32"}, serial = 123456789 },
{ name = "Carl Zeiss Jena 28-70mm f/3.5-4.5 MC Macro Jenazoom Super", focal_length = 35, focal_min = 24, focal_max = 70, manual_aperture = 3.5, f_values = {"3.5","4.5","8","11","16","22","32"}, serial = 123456789 },
{ name = "Lorem_ipsum_dolor_sit_amet,_te_vel_omnis_saepe_laoreet,_ne_pera", focal_length = 35, focal_min = 24, focal_max = 70, manual_aperture = 3.5, f_values = {"3.5","4.5","8","11","16","22","32"}, serial = 123456789 },
{ name = "ALorem_ipsum_dolor_sit_amet,_te_vel_omnis_saepe_laoreet,_ne_peras", focal_length = 35, focal_min = 24, focal_max = 70, manual_aperture = 3.5, f_values = {"3.5","4.5","8","11","16","22","32"}, serial = 123456789 },

--  Zeiss ZF.2 manual lenses Nikon mount - these work with the lens profiles that ship with Adobe Camera Raw

--  { name = "Zeiss Distagon T* 2.8/15 ZF.2",        focal_length =  15, manual_aperture = 2.8 },
--  { name = "Zeiss Distagon T* 3.5/18 ZF.2",        focal_length =  18, manual_aperture = 3.5 },
--  { name = "Zeiss Distagon T* 2.8/21 ZF.2",        focal_length =  21, manual_aperture = 2.8 },
--  { name = "Zeiss Distagon T* 2.8/25 ZF.2",        focal_length =  25, manual_aperture = 2.8 },
--  { name = "Zeiss Distagon T* 2/25 ZF.2",          focal_length =  25, manual_aperture = 2   },
--  { name = "Zeiss Distagon T* 2/28 ZF.2",          focal_length =  28, manual_aperture = 2   },
--  { name = "Zeiss Distagon T* 2/35 ZF.2",          focal_length =  35, manual_aperture = 2   },
--  { name = "Zeiss Distagon T* 1.4/35 ZF.2",        focal_length =  35, manual_aperture = 1.4 },
--  { name = "Zeiss Makro-Planar T* 2/50 ZF.2",      focal_length =  50, manual_aperture = 2   },
--  { name = "Zeiss Planar T* 1.4/50 ZF.2",          focal_length =  50, manual_aperture = 1.4 },
--  { name = "Zeiss Planar T* 1.4/85 ZF.2",          focal_length =  85, manual_aperture = 1.4 },
--  { name = "Zeiss Makro-Planar T* 2/100 ZF.2",     focal_length = 100, manual_aperture = 2   },
--  { name = "Zeiss Apo Sonnar T* 2/135 ZF.2",       focal_length = 135, manual_aperture = 2   },

--  Nikon AF lenses (Autofocus and Vibration Reduction won't work and exact aperture can't be set on G mount lenses)

--  { name = "Nikon AF Fisheye-NIKKOR 16mm f/2.8D",  focal_length =  16, manual_aperture = 2.8 },
--  { name = "Nikon AF NIKKOR 20mm f/2.8D",          focal_length =  20, manual_aperture = 2.8 },
--  { name = "Nikon AF NIKKOR 28mm f/1.4D",          focal_length =  28, manual_aperture = 1.4 },
--  { name = "Nikon AF NIKKOR 35mm f/2D",            focal_length =  35, manual_aperture = 2   },
--  { name = "Nikon AF NIKKOR 50mm f/1.4D",          focal_length =  50, manual_aperture = 1.4 },
--  { name = "Nikon AFS-NIKKOR 50mm f/1.8G",         focal_length =  50, manual_aperture = 1.8 },
--  { name = "Nikon AF Micro-NIKKOR 60mm f/2.8D",    focal_length =  60, manual_aperture = 2.8 },
--  { name = "Nikon AF NIKKOR 85mm f/1.4D IF",       focal_length =  85, manual_aperture = 1.4 },
--  { name = "Nikon AF DC-NIKKOR 105mm f/2D",        focal_length = 105, manual_aperture = 2   },
--  { name = "Nikon AF DC-NIKKOR 135mm f/2D",        focal_length = 135, manual_aperture = 2   },
--  { name = "Nikon AF NIKKOR 28-105 f3.5-4.5D",     focal_length =  28, manual_aperture = 3.5 },

--  Nikon Manual focus lenses

--  { name = "Nikon Zoom Ais ED 50-300",             focal_length = 300, manual_aperture = 4.5 },
--  { name = "Nikon Ais NIKKOR 24mm f/2.8",          focal_length =  24, manual_aperture = 2.8 },
--  { name = "Nikon Ais NIKKOR 35mm f/1.4",          focal_length =  35, manual_aperture = 1.4 },
--  { name = "Nikon Ais NIKKOR 55mm f/1.2",          focal_length =  55, manual_aperture = 1.2 },
--  { name = "Nikon Ais MICRO NIKKOR 55mm f/2.8",    focal_length =  55, manual_aperture = 2.8 },
--  { name = "Nikon Ais NIKKOR 105mm f/1.8",         focal_length = 105, manual_aperture = 1.8 },
--  { name = "Nikon Ais NIKKOR 500mm f/8",           focal_length = 500, manual_aperture = 8   },

--  Samyang manual lenses - also branded as Rokinon and Bower. Cine versions use the same lens profile.
--  The lens profiles for Samyang manual lenses that ship with Adobe Camera raw must be modified in order
--  for automatic lens detection to work.
--  More information here: http://www.magiclantern.fm/forum/index.php?topic=18083.msg176261#msg176261

--  { name = "Samyang 8mm f/2.8 UMC Fisheye",        focal_length =   8, manual_aperture = 2.8 },
--  { name = "Samyang 8mm f/2.8 UMC Fisheye II",     focal_length =   8, manual_aperture = 2.8 }, --   8mm T3.1 Cine
--  { name = "Samyang 8mm f/3.5 UMC Fish-Eye CS",    focal_length =   8, manual_aperture = 3.5 },
--  { name = "Samyang 8mm f/3.5 UMC Fish-Eye CS II", focal_length =   8, manual_aperture = 3.5 }, --   8mm T3.8 Cine
--  { name = "Samyang 10mm f/2.8 ED AS NCS CS",      focal_length =  10, manual_aperture = 2.8 }, --  10mm T3.1 Cine
--  { name = "Samyang 12mm f/2 NCS CS",              focal_length =  12, manual_aperture = 2   }, --  12mm T2.2 Cine
--  { name = "Samyang 12mm f/2.8 ED AS NCS Fisheye", focal_length =  12, manual_aperture = 2.8 }, --  12mm T3.1 Cine
--  { name = "Samyang 14mm f/2.8 ED AS IF UMC",      focal_length =  14, manual_aperture = 2.8 }, --  14mm T3.1 Cine
--  { name = "Samyang 16mm f/2 ED AS UMC CS",        focal_length =  16, manual_aperture = 2   }, --  16mm T2.2 Cine
--  { name = "Samyang 21mm f/1.4 ED AS UMC CS",      focal_length =  21, manual_aperture = 1.4 }, --  21mm T1.5 Cine
--  { name = "Samyang 24mm f/1.4 ED AS IF UMC",      focal_length =  24, manual_aperture = 1.4 }, --  24mm T1.5 Cine
--  { name = "Samyang 35mm f/1.4 AS IF UMC",         focal_length =  35, manual_aperture = 1.4 }, --  35mm T1.5 Cine
--  { name = "Samyang 50mm f/1.2 AS UMC CS",         focal_length =  50, manual_aperture = 1.2 },
--  { name = "Samyang 50mm f/1.4 AS UMC",            focal_length =  50, manual_aperture = 1.4 }, --  50mm T1.5 Cine
--  { name = "Samyang 85mm f/1.4 AS IF UMC",         focal_length =  85, manual_aperture = 1.4 }, --  85mm T1.5 Cine
--  { name = "Samyang 100mm f/2.8 ED UMC MACRO",     focal_length = 100, manual_aperture = 2.8 }, -- 100mm T3.1 Cine
--  { name = "Samyang 135mm f/2 ED UMC",             focal_length = 135, manual_aperture = 2   }, -- 135mm T2.2 Cine
--  { name = "Samyang 300mm f/6.3 ED UMC CS",        focal_length = 300, manual_aperture = 6.3 },


--  Lensbaby lenses

--  { name = "Lensbaby Sweet 35",                    focal_length =  35, manual_aperture = 2.5 },
--  { name = "Lensbaby Sweet 50",                    focal_length =  50, manual_aperture = 2.5 },
--  { name = "Lensbaby Twist 60",                    focal_length =  60, manual_aperture = 2.5 },
--  { name = "Lensbaby Edge 50",                     focal_length =  50, manual_aperture = 3.2 },
--  { name = "Lensbaby Edge 80",                     focal_length =  80, manual_aperture = 2.8 },
--  { name = "Lensbaby Circular Fisheye",            focal_length = 5.8, manual_aperture = 3.5 },
--  { name = "Lensbaby Soft Focus Optic",            focal_length =  50, manual_aperture = 2   },
--  { name = "Lensbaby Double Glass Optic",          focal_length =  50, manual_aperture = 2   },
--  { name = "Lensbaby Single Glass Optic",          focal_length =  50, manual_aperture = 2   },
--  { name = "Lensbaby Plastic Optic",               focal_length =  50, manual_aperture = 2   },
--  { name = "Lensbaby Pinhole Optic",               focal_length =  50, manual_aperture = 19  },
--  { name = "Lensbaby Fisheye Optic",               focal_length =  12, manual_aperture = 4   },
--  { name = "Lensbaby Velvet 56",                   focal_length =  56, manual_aperture = 1.6 },
--  { name = "Lensbaby Velvet 85",                   focal_length =  85, manual_aperture = 1.8 },
--  { name = "Lensbaby Creative Aperture",           focal_length =  50, manual_aperture = 2   },
--  { name = "Lensbaby Sweet 80",                    focal_length =  80, manual_aperture = 2.8 },
--  { name = "Lensbaby Creative Bokeh",              focal_length =  50, manual_aperture = 2.5 },

--  Anamorphic Lenses

--  { name = "Iscorama Anamorphic 50 f/2.8mm ",      focal_length =  50, manual_aperture = 2.8 },

--  Miscellaneous lenses

--  { name = "Kiron Macro 100mm f/2.8",              focal_length = 105, manual_aperture = 2.8 },
}

-- f-number values. Mostly 1/2 Stop
Fnumbers = {"1.0","1.2","1.4","1.6","1.7","1.8","2","2.2","2.4","2.8","3.3","3.5","4","4.5","4.8","5","5.6","6.3","6.7","7.1","8","9.5","11","13","16","19","22","27","32"}

selector_instance = selector.create("Select Manual Lens", lenses, function(l) return l.name end, 600)

-- Flag variable used in LV Handler and menu
lensSelected = false

-- Property to be written in .xmp file
xmp:add_property(xmp.lens_name, function() return lens.name end)
xmp:add_property(xmp.focal_length, function() return lens.focal_length end)
xmp:add_property(xmp.aperture, function() return (lens.manual_aperture * 10) end)
xmp:add_property(xmp.lens_serial, function() return lens.serial end)

-- Helper function
function is_manual_lens()
  -- Adapter with no AF Chip -> ID = 0
  -- Adapter with AF confirm Chip -> name and focal length "1-65535mm"
  if (lens.id == 0 or lens.name == "1-65535mm" or lens.name == "(no lens)") then
    return true
  else
    return false
  end
end

-- Function used to make sure all additional attributes are correct when switching lens,
-- as if the new lens doesn't have the same attribute, old values don't get overwritten in lens_info
-- Get called in update_lens() before setting value of the new lens
function reset_lens_values()
  lens.focal_length = 0
  lens.focal_min = 0
  lens.focal_max = 0
  lens.serial = 0
end

-- Function used to restore lens value of selected lens after changing shooting mode
-- Get called in property.LENS_NAME:handler() after checking attached lens is manual
function restore_lens_values()
  local index = lens_config.Lens
  if (index ~= nil and index ~= 0 and lens_config ~= nil) then
    -- Restore Lens Info
    for k,v in pairs(lenses[selector_instance.index]) do
        lens[k] = v
    end
    -- Restore last Aperture and Focal Length used from lens.cfg
    lens.focal_length = lens_config["Focal Length"]
    lens.manual_aperture = lens_config["Aperture"]
    lens.exists = true
  end
end

--  Handler for lens_name property
--  Get Called when:
--  Switching lens
--  Switching shooting mode
function property.LENS_NAME:handler(value)
    if is_manual_lens() then
        -- If we are changing shooting mode, restore values and don't prompt again for lens selection
        if lensSelected then
          -- Restore lens value as before changing shooting mode
          restore_lens_values()
        else
          task.create(select_lens)
        end
    else
      -- Not a manual Lens, no need to write sidecar file
      if selector_instance ~= nil then
          selector_instance.cancel = true
      end
      xmp:stop()
      -- Reset selection in lens.cfg. Note: ML will save automatically new .cfg
      lens_menu.submenu["Lens"].value = 0
      -- Clear flag for next run
      lensSelected = false
    end
end

--  Handler for LV Lens Length property
--  Get Called when entering LV
--  Otherwise a "50mm" focal length will be displayed and saved to metadata
--  Also fix Aperture when using AF Confirm chip
function property.LV_LENS:handler(value)
    -- Update length only if we are using a manual lens
    if lensSelected == true then
      -- Update attribute from selected lens
      lens.focal_length = lens_menu.submenu["Focal Length"].value
      lens.manual_aperture = lens_menu.submenu["Aperture"].value
    end
end

-- Open lens selection Menu
function select_lens()
    if #lenses > 1 then
        local menu_already_open = menu.visible
        if not menu_already_open then
            menu.open()
            display.rect(0, 0, display.width, display.height, COLOR.BLACK, COLOR.BLACK)
        end
        if selector_instance:select() then
            update_lens()
            update_menu(0)
        end
        if not menu_already_open then
            menu.close()
        end
    elseif #lenses == 1 then
        update_lens()
        update_menu(0)
    end
end

-- Copy lens attribute from lenses and write to .xmp file
-- Note: Content of lens.cfg is automatically saved by ML after closing ML menu
function update_lens()
    -- Reset lens_info structure to get correct values in Lens Info Menu and Metadata
    reset_lens_values()
    -- Update attribute from selected lens
    for k,v in pairs(lenses[selector_instance.index]) do
        lens[k] = v
    end
    -- Allow to write sidecar
    xmp:start()
    -- Update flag
    lensSelected = true
    -- Allow to write values in Lens Info Menu
    lens.exists = true
end

lens_menu = menu.new
{
    parent = "Lens Info Prefs",
    name = "Manual Lens",
    help = "Info to use for attached non-chipped lens",
    icon_type = ICON_TYPE.ACTION,
    submenu =
    {
        {
          name = "Lens",
          help    = "Select Manual Lens",
          unit    = UNIT.DEC,
          select = function()
                    -- Select a new lens only when not using a lens with AF
                    if is_manual_lens() or lensSelected == true then
                      task.create(select_lens)
                   end end,
          update = function(this)
                    -- Update integer value to be saved in lens.cfg
                    this.value = selector_instance.index
                   end,
          rinfo = function()
                    return lens.name
                  end,
          warning = function()
                      if lensSelected == false then
                        return "No lens selected"
                      else if is_manual_lens() == false then
                        return "Chipped Lens detected. Only manual lens with AF Chip can change this."
                      end end
                    end,
        },
        {
            name    = "Focal Length",
            help    = "Focal length to be saved in metadata",
            -- Min and Max are updated when a lens is selected from menu
            min     = 8,
            max     = 400,
            unit    = UNIT.DEC,
            -- Update Focal Length with selected value from submenu
            update = function(this)
                      -- A "0" is returned by menu when focal_min and focal_max are missing from lens attribute
                      if lensSelected == true and this.value ~= 0 then
                        lens.focal_length = this.value
                      else
                        -- Prime lens. Reset menu value to the corrected one
                        this.value = lens.focal_length
                      end end,
            warning = function()
                        if is_manual_lens() == false then
                          return "Chipped Lens detected. Only manual lens with AF Chip can change this."
                        else if lensSelected == false then
                          return "No lens selected"
                        else if lens.focal_min == lens.focal_max then
                          return "Chan be changed only for manual-focus Zoom lens"
                        end end end
                      end,
        },
        {
            name    = "Aperture",
            help    = "Aperture to be saved in metadata",
            choices = Fnumbers,
            -- Update Aperture with selected value from submenu
            update = function(this)
                      if lensSelected == true then
                        lens.manual_aperture = tonumber(this.value)
                      else
                        -- Reset menu value to the corrected one
                        this.value = lens.manual_aperture
                      end end,
            warning = function()
                        if is_manual_lens() == false then
                          return "Chipped Lens detected. Only manual lens with AF Chip can change this."
                        else if lensSelected == false then
                          return "No lens selected"
                        end end
                      end,
        }
    },
    submenu_width = 700,
    rinfo = function()
        return lens.name
    end,
    warning = function()
        if is_manual_lens() == false then
            return "Chipped lens is attached"
        end
    end
}
autoload_menu = menu.new
{
    parent = "Lens Info Prefs",
    name = "Autoload Lens",
    help = "Restore lens config from .cfg after camera Power On/Wake Up",
    choices = {"Off","On"}
}

-- Helper function for update_menu()
-- Search for a specific value in a table
-- Return position index of val when found, otherwise return first index
function get_value_index (table, val)
    for index, value in ipairs(table) do
        if value == val then
            return index
        end
    end
    -- Value not found
    return 1
end

-- Update the menu with values for Focal Length and Aperture from selected Lens
-- To be called when switching manual lens
function update_menu(copy)
  local index = selector_instance.index
  if(index == 0) then return end

  -- Update selection and Focal Length
  lens_menu.submenu["Lens"].value = index
  lens_menu.submenu["Focal Length"].min = lens.focal_min
  lens_menu.submenu["Focal Length"].max = lens.focal_max

  -- Update field "Choices" in menu for aperture selection
  if lenses[index].f_values then
    -- Lens selected has custom aperture value. Use .f_values table from lens instead of generic f-numbers
    lens_menu.submenu["Aperture"].choices = lenses[index].f_values
  else
    local tmp = {} -- Used to save value from table.move
    -- Generate a subset of Fnumbers starting from max Apeture (manual_aperture attribute) of the selected lens
    local start = get_value_index(Fnumbers,tostring(lenses[index].manual_aperture))
    -- Retrive f-number array size
    local size = #Fnumbers
    -- Retrive subset of Fnumbers table and set to menu
    lens_menu.submenu["Aperture"].choices = table.move(Fnumbers, start, size, 1, tmp)
  end

  -- Check whenever need to load values from .cfg or not
  if copy == 1 then
    -- Assign Aperture and Focal Length from .cfg
    lens_menu.submenu["Focal Length"].value = lens_config["Focal Length"]
    lens_menu.submenu["Aperture"].value = lens_config["Aperture"]
  else
    -- Assign manual_aperture from lenses as default aperture value when lens is selected
    lens_menu.submenu["Focal Length"].value = lens.focal_length
    lens_menu.submenu["Aperture"].value = lens.manual_aperture
  end
end

-- Create lens.cfg base on "Manual Lens" menu field
lens_config = config.create_from_menu(lens_menu)
autoload_config = config.create_from_menu(autoload_menu)

-- Check precence of manual lens on start and autoload values if the user enabled autoload
if is_manual_lens() then
  local id = tonumber(lens_config.Lens)
  autoload = autoload_menu.value == "On"

  if autoload and id ~= 0 then
    selector_instance.index = id
    restore_lens_values()
    update_menu(1)
    lensSelected = true
    xmp:start()
  else
    -- Prompt menu for lens selection
    task.create(select_lens)
  end
end
