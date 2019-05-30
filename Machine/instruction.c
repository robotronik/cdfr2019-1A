 PID_Configuration pid_conf_sum = {.Kp = 10,
  .Ki = 0,
  .Kd = 0,
  
  .max_eps = 100000000,
  .position_tolerance = 3,
  .speed_tolerance =1
  };

  PID_Configuration pid_conf_diff = {.Kp = 500,
  .Ki = .0,
  .Kd = .0,
  
  .max_eps = 100000000,
  .position_tolerance = 3,
  .speed_tolerance =1
  };
  PID_Status pid_sum = {0};
  PID_Status pid_diff = {0};
 
 volatile Odometry odometry_true;
 volatile Odometry odometry; 
//global pid_sum,pid_diff, odometry

void init(){
	pid_init(&pid_sum,&pid_conf_sum);
	pid_init(&pid_diff,&pid_conf_diff);
}
 
void getOdometry(double* sum, double* diff){
	*sum = odometry.x;
	*diff = odometry.theta;
} 
 
int avancer(double dest){
	double sum,diff;
	getOdometry(sum,diff);
	
	double voltage_sum = pid(&pid_sum,dest-sum);
    double voltage_diff = pid(&pid_diff,0-diff);

    double voltage_l = voltage_sum - voltage_diff;
    double voltage_r = voltage_sum + voltage_diff;
	
	motorControl(&htim3,(int)(voltage_l),1);	
	motorControl(&htim3,(int)(voltage_r),0);

	if(reached(pid_sum)){
		return 1;
	}
	else{
		return 0;
	}	
}
  
void stop(){
	motorControl(&htim3,0,1);	
	motorControl(&htim3,0,0); 
}

