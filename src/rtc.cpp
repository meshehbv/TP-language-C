#include "rtc.h"
//RTC objects
RTC_DS1307 rtcDevice;
void rtc_init()
{
if(!rtcDevice.begin())
{
return;
}
if (!rtcDevice.isrunning())
{
rtcDevice.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
}
DateTime rtc_get_current_time()
{
return rtcDevice.now();
}
void rtc_set_current_time(DateTime datetime)
{
if(!datetime.isValid()) return;
rtcDevice.adjust(datetime);
}