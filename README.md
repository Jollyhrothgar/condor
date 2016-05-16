#README FOR "make_condor_jobs.pl"

This tool was written to enable streamlining of creating and running condor job
files. Often times, we have a large data set, which can be split into
arbitrarily smaller data sets, which all need processing by a function or group
of funtions. In the author's experiance, the common experiance can be boiled
down to the following scenario:

  1. There is some data set we wish to process it, stored over many files such
  as: root_tree_1.root, root_tree_2.root...etc.

  2. We have compiled a set of functions into a library, which are called via a
  root macro, such as: process_file.C

  3. This macro takes a set of arguments, which interactively, might be fed to
  the macro like so:

    ~> process_file.C'("root_tree_1.root","some_arg",...,"outfile.root")'
  
This process can be repeated for as many files as we want, but, condor allows us
the option to farm out each instance of "process_file.C" to a computing grid.
The setup of such a system is usually tedious. This script's purpose is to make
that process easy. There are two ways to use this script. First, is the most
simple way - and will simply take an executable script, (such as one that
contains a specific call to "process_file.C" - lets call it "process_file.sh") 
and generate a job file. It assumes that all logs and other 'condor-generated' 
files will be named similarly to the script (i.e process_file.out,
process_file.job, process_file.err, process_file.log). The other, more powerful
operation mode of this script is summarized as follows:

# Example Usage
  1. Create a config file:
  
    ~> make_condor_jobs.pl --generate

  2. Modify the new file, "setup.conf" to suit your environment's needs.
  
  3. Create a file containing white-space separated arguments that need to be
  fed to your root macro. In our example, lets further refine the 'arguments'
  needed by our root macro - lets say that this macro needs:
    - string
    - int
    - float
    - string
  And further, give dummy values for this arguemnts, such that, interactively,
  your script could be called with:

    ~> root -l -b -q process_file.C'("the_string", 42, 35.2382, "other_str")

  If you have a text file, listing (white-space-separated) arguments for each
  instance of your macro, per line, then these root calls will be constructed
  from each line of your text file, shoved into a bash script, and an associated
  .job file will be generated. A script will also be created which can be used
  to submit all jobs that were generated.

  3. Create the .job files, .sh files based on what you wrote in the setup.conf
  file.
    
    ~> make_condor_jobs.pl --make-jobs

  4. Run the condor_submit.sh script that was generated yourself, or
  alternatively, make the jobs and then submit them with:

    -> make_condor_jobs.pl --create-and-submit

---EXAMPLE-CODE---
In the folder called "example", there is a fully configured environment for
running this script to generate jobs.

Test_Condor.C -> an example root macro which we want to distribute to condor
  with various arguments
setup.conf -> a filled out setup.conf file generated with 
  make_condor_jobs.pl --generate
make_condor_jobs.pl -> the scrip which handles setup of condor jobs
generate_random_arguments.C - compile this with 
  g++ generate_random_arguments.C -o random_args.exe
  run to make a txt file containing arguments needed for "Test_Condor.C"
jobs - folder to store .job files
logs - folder to store .log, .out, and .err fikes
scripts - folder to store scripts executed on various nodes
output - folder to store output of conodr jobs
