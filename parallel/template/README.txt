When we run jobs in parallel through condor, we are effectively spreading the computing time needed to process 'N' events across 'n' servers. This can be useful for a variety of reasons

a) You would like to run 500 billion events in Pythia. Typically, this would take many, many days to run. However, if you split this task amongst 1000 servers, each simulating 500 million events, the task will be completed within the day. You can merge the 1000 output files into one, and then do data analysis with this larger file

b) You want to run some e+p collisions however, for some reason or the other, you want to test all beam energies ranging from 5x50GeV to 5x250GeV, with 0.01GeV increments. Well, you would then need to simulate a unique event for each Pythia runcard, so you could use a macro to generate the 20000 runcards and then use Condor to run 20000 simulations

create_condor_jobs.C will create a certain, user defined amount, of condor jobs and subsequent sh files. Each condor job will be named differently. Each job file is linked to a unique .sh whose command (in the template) is to run hello_world.C. The runTheJobs.sh file which is created after executing "root -l create_condor_jobs.C" will submit all the .job files at once. 
