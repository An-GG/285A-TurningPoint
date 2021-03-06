#include "vex.h"
#include "config/config.h"
#include "assistants/assistants.h"
#include "selector/selector.h"
#include "autons/autons.h"
#include "drivecontrol/drivecontrol.h"

using namespace vex;



void pre_auton( void ) {
  vex::task t4(GUI);
  vex::task blink(ledBlinkLoop);
  Gyro.startCalibration(5000);
  blinkLED = true;
  vex::task::sleep(6000);
  blinkLED = false;
  blink.stop();
}



void autonomous( void ) {
  vex::task::sleep(150);
  autonState = 10;
  execute();
}



void usercontrol( void ) {
  //GUI
  vex::task t4(GUI);

  //TELEMETRY
  vex::task t3(telemetryTask);
  LED.set(true);

  //DESCORER
  vex::task t1(descorerTask);

  //INTAKE
  vex::task t2(intakeTask);

  //FLYWHEEL
  flywheel.spin( directionType::rev, 540, velocityUnits::rpm);


  //DRIVE CONTROL
  drivecontrol();
  // Nothing below drive control will run, drivecontrol() is an infinate loop.
}





int main() {

    //Run the pre-autonomous function.
    pre_auton();

    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }

}
