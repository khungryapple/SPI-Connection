#include "WPILib.h"
#include "Timer.h"
#include "SPI.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	SPI* spi;
	unsigned char buffer[1]; //saves input from lidar in byte array
	unsigned char dataToSend[0];
	unsigned char size = 8;
	int distance; //distance calculated in cm

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);

		//Initialize the I2C connectin on address 84
		spi = new SPI(SPI::Port::kOnboardCS0); //you can change the port; kOnboardCS0-3
		spi->Init();
		spi->SetClockRate(500000);
		spi->SetMSBFirst();
		spi->SetSampleDataOnFalling();
		spi->SetClockActiveLow();
		spi->SetChipSelectActiveLow();
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		spi->Read(true, buffer, size); //(bool initiate, uint8_t* dataReceived, uint8_t size)
		distance = (int)((buffer[0] <<8) + buffer[2]);
		SmartDashboard::PutNumber("Distance", distance);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
