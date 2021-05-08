
extern void setupEC(void);
extern float rawECRaw(void);
extern float generateEC(void);
extern float generateEDS(void);

extern void setuppH(void);
extern float averageArr(void);
extern float readpH(void);
extern float calculatepH(void);

extern void setupRTC(void);
extern void setRTC(void);
extern String logTime(void);

extern void setupSD(void);
extern void logData(String);

extern void setupLCD(void);
extern void readTouch(void);
extern void TFTdisplay(void);

extern void setupTemp(void);
extern void readTemperatures(void);
extern float generateTemperatureC(void);
extern float generateTemperatureF(void);

extern void setupTurb(void);
extern float readTurbidity(void);
extern float calculateTurbidity(void);
