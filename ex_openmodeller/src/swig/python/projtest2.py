import om;

mod = om.OpenModeller();
print "Welcome to openModeller Python Binding test.\n";
print "Using openModeller version:     ", mod.getVersion();
print "Loading algorithms from:        ", mod.getPluginPath();
print "Algorithms loaded:              ", mod.loadAlgorithms();
print "Number of available algorithms: ", mod.numAvailableAlgorithms();

#md = mod.algorithmMetadata("MinimumDistance");
md = mod.algorithmMetadata("GARP");
#md = mod.algorithmMetadata("CSM");

print "Algorithm info: ";
print "Id:             ", md.id;
print "Name:           ", md.name;
print "Version:        ", md.version;
print "Author:         ", md.author;
print "Contact:        ", md.contact;

maps = ["aspect", "dem", "slope", "dtr", "prec", "temp", "wet"];

# GARP Parameters
params = [["MaxGenerations",   "25"], 
          ["ConvergenceLimit", "0.0"],
          ["PopulationSize",   "50"],
          ["Resamples",        "2500"],
          ["MutationRate",     "0.25"],
          ["CrossoverRate",    "0.25"]];


# CSM
#params = [];

#min dist
#params = [["MaxDist", "0.1"]];

wktsys = "GEOGCS[\"WGS84\", DATUM[\"WGS84\", SPHEROID[\"WGS84\", 6378137.0, 298.257223563]], PRIMEM[\"Greenwich\", 0.0], UNIT[\"degree\", 0.017453292519943295], AXIS[\"Longitude\",EAST], AXIS[\"Latitude\",NORTH]]";
spfile = "Strix_varia.txt";
spname = "Strix varia";

ocfile = om.OccurrencesFile(spfile, wktsys);
ocfile.tail();
occurr = ocfile.remove(spname);

print "\nInitializing algorithm.";
print "Reading occurrences.        ", mod.setOccurrences(occurr);
print "Setting Environment object. ", mod.setEnvironment(0, [], 7, maps, "mask");
print "Setting algorithm params.   ", mod.setAlgorithm(md.id, 6, params); # GARP
#print "Setting algorithm params.   ", mod.setAlgorithm(md.id, 0, params); #CSM
#print "Setting algorithm params.   ", mod.setAlgorithm(md.id, 1, params); #mindist
print "Running algorithm.          ", mod.run();
print "Setting output map          ", mod.setOutputMapByFile(255, "map.tif", "mask", "mask");
print "Creating output map.        ", mod.createMap(mod.getEnvironment(), "map.tif", "mask");

projmaps1 = ["aspect", "OMProjDS/elev_times2/dem_2x", "slope", "dtr", "prec", "temp", "wet"];
projmaps2 = ["aspect", "dem", "slope", "dtr", "prec", "OMProjDS/climate_plus2dg/temp_pls2dg", "wet"];

projenv1 = om.Environment(wktsys, 0, [], 7, projmaps1, "mask");
projenv2 = om.Environment(wktsys, 0, [], 7, projmaps2, "mask");

print "Setting output map                   ", mod.setOutputMapByFile(255, "", "mask", "mask");
print "Creating projection map (elevation): ", mod.createMap(projenv1, "elevproj.tif", "mask");
print "Creating projection map (climate):   ", mod.createMap(projenv2, "climproj.tif", "mask");

print "Finalizing processing.";

print "\nThanks for using openModeller.";
print "Good bye!\n";

