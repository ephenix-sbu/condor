#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
TString convert_int_to_TString(int a);
TString convert_double_to_TString(double a);
int create_condor_jobs()
{
  /* --------------------------------------------------------
   */
  TString username             = "gregtom3";
  TString email                = "gregcondorjobs@gmail.com";
  TString initial_dir          = "/sphenix/user/gregtom3/";
  TString location_of_job_file = "/sphenix/user/gregtom3/ephenix-sbu/condor/parallel/template"; // no slash after final directory
  TString location_of_sh_file  = location_of_job_file;
  const int number_of_jobs = 5;
  const int ROOT_VERSION = 5; // or use 6
  /* --------------------------------------------------------
   */
  std::ofstream outRun ("runTheJobs.sh");
  for(int j = 0; j < number_of_jobs ; j++)
    {

      /* --------------------------------------------------------
   */
      TString unique_job_name = "job_" + convert_int_to_TString(j);
      TString where_the_code_is = "/sphenix/user/gregtom3/ephenix-sbu/condor/parallel/template";
      TString what_code_to_execute = "root -l hello_world.C";
      /* --------------------------------------------------------
   */

      TString outnameT = location_of_job_file+"/"+unique_job_name;
      TString sh_nameT = outnameT+".sh";      
      TString out_nameT = outnameT+".out";
      TString err_nameT = outnameT+".err";
      TString log_nameT = outnameT+".log";
      TString job_nameT = outnameT+".job";
      std::ofstream outJob (job_nameT.Data());
      outJob << "Executable = " << sh_nameT << "\n";
      outJob << "Requirements = (CPU_Experiment == \"phenix\")\n";
      outJob << "PeriodicHold = (NumJobStarts>=3 && JobStatus == 1)\n";
      outJob << "Output = " << out_nameT << "\n";
      outJob << "Error = " << err_nameT << "\n";
      outJob << "Log = " << log_nameT << "\n";
      outJob << "Universe = vanilla \n";
      outJob << "Priority = +0\n";
      outJob << "Input = /dev/null\n";
      outJob << "GetEnv = False\n";
      outJob << "Initialdir = " << initial_dir << "\n";
      outJob << "+Experiment= \"sphenix\"\n";
      outJob << "+Job_Type = \"cas\"\n";
      outJob << "Notification = Always\n";
      outJob << "Notify_user = " << email << "\n";
      outJob << "Queue\n";
      
      outJob.close();
      
      std::ofstream outSh(sh_nameT.Data());
      outSh << "#!/bin/tcsh\n";
      outSh << "setenv HOME /sphenix/u/" << username << "\n";
      outSh << "source /etc/csh.login\n";
      outSh << "foreach i (/etc/profile.d/*.csh)\n";
      outSh << "\t source $i\n";
      outSh << "end\n";
      if(ROOT_VERSION==5)
	outSh << "source /opt/sphenix/core/bin/sphenix_setup.csh -n root5\n";
      else if(ROOT_VERSION==6)
	outSh << "source /opt/sphenix/core/bin/sphenix_setup.csh \n";
      //      outSh << "setenv LD_LIBRARY_PATH \"/sphenix/user/"<<username<<"/install/lib:$LD_LIBRARY_PATH\"\n"; If needed you can include the LD_LIBRARY_PATH
      outSh << "cd " << where_the_code_is << "\n";
      outSh << what_code_to_execute << "\n";
      outSh.close();
      outRun << "condor_submit "<<job_nameT<<"\n";
    }
  outRun.close();
  std::system("chmod +x ./runTheJobs.sh");
  return 0;
}

TString convert_int_to_TString(int a)
{
  TString temp;
  
  std::stringstream ss; 
  ss<<a;
  string s = ss.str();
  temp = TString(s);
  return temp;
}
TString convert_double_to_TString(double a)
{
  TString temp;
    
  std::stringstream ss; 
  ss<<a;
  string s = ss.str();
  temp = TString(s);
  return temp;
}

