ReadMe =========================================================================
                        WIN32 APPLICATION: Fractals_***
================================================================================
  


                This WinApi Poor-Intellect Program is
                made by Tishka17 
                assistance (beer, music, chat, girls)
                by Toxa.su aka heil0 and =ValKir= aka Sir Waller
                thanks to Ftvkun for making first releases of program


  
   Last version: 10.05.2007
  
   Changes in code:

10.05.2007

   fixed: incorrect direction chose in walking plugin
   updated: repeated cell generating in TumpliersCross generating
   
08.05.2007
   
   updated: front of walks in WalkingLine is now calculated for each horisontal line separatly (no using of sectors)
   added: 2d kantors dust (Cuntors cluster) in Generator plugin
   added: TamplierCluster in Generator plugin (many crosses inside)
   
07.05.2007

   updated: front of walks in WalkingLine is now calculated by Expectance but not maximum of distance
   
15.04.2007
   
   added: walking from a line in RandomWalks plugin

11.03.2007

   added: made /A option work in set command in script interpreting (calculating expressions)
   
09.01.2007

   added: after week of working tishka17 made new script language interpreter
   added: automatically running scripts
   updated: all function loaded from dlls now stored in on SDLLs structure
   
23.12.2006

   fixed: console.exe used to finish its work when incorrect command entered
   added: loading function's parameters from file
   added: console input in input.dll
   fixed: incorrect front was generated in random walkes plugin
   fixed: errors in redrawing of menus
   added: making different layers (int random walks) in case of what user wants
   
22.12.2006

   added: drawing of layers
   fixed: plugins' methods were called twice after input of parameters
   fixed: calls of methods which do not neet any params were not written in log
   
18.12.2006

   fixed: separator move to position 0 when main window is minimized
   
16.12.2006

   fixed: functions with no parameters could not been called
   added: function of unknown type (ftUnknown) is now shown as separator in gui_.exe in menu
   added: new command line parameter ("/?") for console.exe
   added: some of the help files
   
14.12.2006
    
   fixed: there were incorrect messages sent when choose layer in picture panel menu
   added: front of diffusion in randomwalks plugin
   fixed: panels' menus didn't refresh after function call
   fixed: choosing recent files didn't call readdata function
   fixed: input gui dialogs didn't work
   
13.12.2006

   added: saving recent files list
   fixed: separator bar hided when dragging
   
12.12.2006
   
   added: correct working of panels view menu
   added: disabling any or both of panels
   added: saving main window size to settings file
   updated: layers in plugins
   
10.12.2006

   added: two panels are now parts of main window, with movable separator between them
   added: panels menu, which does not work now
   fixed: creating window in GUI_.exe maked plugins ot work
   fixed: could not show log file
   
05.12.2006

   updated: rewritten console version of analyser using new directories structure (using common files)
   updated: when bat file finished console program waits for input from terminal
   fixed: not loaded input.dll in console.exe
   updated: author in settings file, new standart comments
    
02.12.2006

   updated: rewritten dlls and plugins using common files
    
22.11.2006
    
   updated: input dialog moved to a separate dll
    
21.11.2006   
    
   updated: plugins to use different parameters in functions (except dialog to input parameters)
  
18.11.2006   

   added: input dialog in interface (temporaly it's called by help menu item)[but it doesn't work properly] 
  
03.11.2006      

   added: in RandomWalks plugin: output values 20 times while one walking
  
28.10.2006   

   added: function can return string to be written in log file; 
         added such string into ReadData function; RandomWalks plugin's functions;
   updated: all project files in separate directory
   added: new good Random generator in RandomWalk plugin
  
08.10.2006   

   updated: chabged static constants in classes to enum
   updated: new directories structure (project in separate directory)
   added: random walk plugin with 2 methods in it
     
30.09.2006   

   updated: language & settings files
   added: permanent dlls (graphics, readdata, approximation) path in settings.ini
   added: panels position menu (such items as Tile Horisontally, Cascade and so on)
   added: hot keys help file & link to web site in help menu
     
17.09.2006   
   fixed: tab character was ig  red in any ini-files (e.g. language file)
  
03.07.2006     
   fixed: if any function is   t found in plugin, it was unloaded (even if there are any other functions)
   rewritten: logfile.h, dll's.h and plugin.h are   w global for interface and console versions
  
02.07.2006    
   added [interface] : running batch files from fractals_interface (executes console version)   
   added [log]: writes what version (console or interface) of analyzer was started/finished
   added: saving settings in .ini file. (  w that's just lng and hlp files path)
  
28.06.2006   

   added: fractals_console   w writes if it could run a method or   t (it ig  res empty strings as methods call)
   added: some methods in fractals_console: "Echo" and "Pause"
  
25.06.2006   

   rewritten: language file to use .ini format
   added: ini files unit (FileIni.cpp & FileIni.h)
  
30.05.2006   

   added: several filters (hue and saturation [RGB to HSV Smit's alhorythm])
   added: restoring panels after calculation
     
29.05.2006      

   added: language file
   added: points-  ise removable filter
  
20.05.2006   

   added: AutoLevels and ContrastMo  hromize methods in Filter plugin
  
12.05.2006   

   added: some functions in fractals_console (such as WriteLog, WriteLogError, ListMethods)
   added: BW filter, which inverts colors
   fixed: When 24b picture was loaded, program losed last column
   fixed: zooming of picture when drawing was   t to full window
  
11.05.2006   

   added: loading of colored pictures
   added: plugin with filters: mo  chromization and extracting borders
  
28.04.2006   

   released console version of program
   added: class of Color Picture with up to 32 bit depth of color
   added: prototypes of Color and Black&White+Color filters
  
29.03.2006   

   added: Hausdorf into dimension plugin
   added: drawing of parabolas and other poly  mial graphics
  
12.03.2006   

   fixed: when graphic is deleted program still tries to draw it, so drawing is disabled after each plugin method call
   added: menu with sizes of squares to draw
  
09.03.2006   
   finished with realisation of plugins
   removed: old dll's
   rewritten _graphics for compatibility with plugins
   updated: graphics selection menus: you can choose what you want to see in each panel
   fixed: when launchig plugin function message differed in release from debug versions
    
22.02.2006      

   added: new plugin, which can calculate Minkovsky dimension.
   added: automated mounting of plugins
  
21.02.2006   

   added: rewritten approximation unit. New version of it will be used during the work of plugins
  
20.02.2006   
    
   started working with plugins. First plugin is released: Generator. Waiting for some editions in plugins realisations.  
   added: "plugins" menu item
  
04.02.2006                         

   updated: log file is   w written in HTML format
  
28.12.2005   

   updated: was moved "Generate kokh" item to Calculate menu
   removed some bugs during using accel table
   updated: log file was placed to exe directory
  
27.12.2005   
 
   added time into log file
  
25.12.2005   

   updated:   w Fractals_Interface writes log file during all it's work
  
23.12.2005   

   added: new function (DrawWithSquaresPicture), loaded from Graphics_.dll
   begin testing alhorythm of swimming squares
  
09.12.2005   

   added menu item "Calculate/DrawSquares", which is like CheckBox
  
15.11.2005   

   added some comments
   updated: moved GenerateKokh function into separate file
  
04.06.2005   
  
03.06.2005   
  
02.06.2005   

   added LoadGraphics_ function into "DLLs.h" (nedded to load graphics_.dll and functions from it)
  
27.05.2005   
   added "DLLs.h", with types and functions to load procedures from Minkovsky and MinSquares dlls
   added open/save file dialogs
   added global data variables
  
04.05.2005   

   added marks in menu items such as "View/Picture", "View/Graph"
   added icons to program messages
   updated: maked reflection style in "Help/About" messagebox
   updated: item "File/Save" maked shaded as default
   added accelerators of program (hotkeys)
   added menu item "Calculate"
   added menu item "Calculate/Calculate now"
   added "help/help"
  
29.04.2005   

   beginning work on interface.
   added: function of the Cutting the right-bottom corner
   writtened items menu "file", "view", "help"
   writtened function "file/exit" and "help/about"
