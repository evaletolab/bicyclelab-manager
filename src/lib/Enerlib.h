/*
Enerlib: easy-to-use wrapper for AVR's Sleep lib.
By E.P.G. - 11/2010 - Ver. 1.0.0
*/

#ifndef Ecolib_h
#define Ecolib_h

class Energy
{
  private:
    bool sleeping;
	public:
    Energy();
		void PowerDown(void);
		void Idle(void);
		void SleepADC(void);
		void PowerSave(void);
    void Standby(void);
    bool WasSleeping(void);
};

#endif