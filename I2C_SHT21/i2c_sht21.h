/*
 
*/

#ifndef i2c_sht21_H
#define i2c_sht21_H

#define sht21_DEVID 0x40

class i2c_sht21
{
	public:
		i2c_sht21();
		void init(int i2c_devid);
		
		float readTemp(void);
		float readHumidity(void);

	private:
		int _devid;
		void Softreset(void);
		int readData(int befehl);
		float temperatur=0;
		float humidity=0;
	
};




#endif
