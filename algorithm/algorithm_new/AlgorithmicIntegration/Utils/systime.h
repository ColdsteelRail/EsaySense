#pragma once
struct PRECISETIME{
 	unsigned short wYear;
 	unsigned short wMonth;
 	unsigned short wDayOfWeek;
 	unsigned short wDay;
 	unsigned short wHour;
 	unsigned short wMinute;
 	unsigned short wSecond;
 	unsigned short wMilliseconds;
 };



#include <string>
#include <stdint.h>
using namespace std;
class  CMilliSecSpan
{
public:
	CMilliSecSpan() throw();
	CMilliSecSpan( int64_t time ) throw();
	CMilliSecSpan( int lDays, int nHours, int nMins, int nSecs, int nMillisecond) throw();

	int64_t GetTotalDays() const throw();
	int64_t GetTotalHours() const throw();
	//long GetHours() const throw();
	int64_t GetTotalMinutes() const throw();
	//long GetMinutes() const throw();
	int64_t GetTotalSeconds() const throw();
	//long GetSeconds() const throw();
	int64_t GetTotalMilliSeconds() const throw();
	//long GetMilliSeconds() const throw();


	int64_t GetTimeSpan() const throw();

	CMilliSecSpan operator+( CMilliSecSpan span ) const throw();
	CMilliSecSpan operator-( CMilliSecSpan span ) const throw();
	CMilliSecSpan& operator+=( CMilliSecSpan span ) throw();
	CMilliSecSpan& operator-=( CMilliSecSpan span ) throw();
	bool operator==( CMilliSecSpan span ) const throw();
	bool operator!=( CMilliSecSpan span ) const throw();
	bool operator<( CMilliSecSpan span ) const throw();
	bool operator>( CMilliSecSpan span ) const throw();
	bool operator<=( CMilliSecSpan span ) const throw();
	bool operator>=( CMilliSecSpan span ) const throw();

private:
	int64_t m_timeSpan;
};
#define  GetLocalPreciseTime CPreciseTime::GetLocalTime
class  CPreciseTime
{
public:
	/*static CPreciseTime  GetCurTime();*/
	static PRECISETIME GetLocalTime();
	CPreciseTime(bool bInitbylocaltime= false);
	CPreciseTime( int64_t time ) throw();
	CPreciseTime(const char* strtime);
	CPreciseTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,int nMillisecond,
		int nDST = -1 );
	CPreciseTime( const PRECISETIME& st, int nDST = -1 );

	CPreciseTime& operator=( int64_t time ) throw();

	CPreciseTime& operator+=( const CMilliSecSpan &span ) throw();
	CPreciseTime& operator-=( const CMilliSecSpan &span) throw();

	CMilliSecSpan operator-( const CPreciseTime& time ) const throw();
	CPreciseTime operator-( const CMilliSecSpan &span ) const throw();
	CPreciseTime operator+( const CMilliSecSpan &span) const throw();

	bool operator==( const CPreciseTime& time ) const throw();
	bool operator!=( const CPreciseTime& time ) const throw();
	bool operator<( const CPreciseTime& time ) const throw();
	bool operator>(const CPreciseTime& time ) const throw();
	bool operator<=( const CPreciseTime& time ) const throw();
	bool operator>=( const CPreciseTime& time ) const throw();

	

	int64_t MkTime() const throw();

	int GetYear() const throw();
	int GetMonth() const throw();
	int GetDay() const throw();
	int GetHour() const throw();
	int GetMinute() const throw();
	int GetSecond() const throw();
	int GetMillisecond() const throw();
	int GetDayOfWeek() const throw();

	string Format(bool bSec = true) const throw();

private:
	int64_t m_time;
};


class  CMilliSecElapse
{
public:
	CMilliSecElapse();
	CMilliSecElapse(const CMilliSecElapse & rt);

	CMilliSecElapse & operator = (const CMilliSecElapse & rt);
	
	void Reset();
	int64_t Elapsed();
	static unsigned long GetTickCount_stc();
private:
	//用于计时
	uint32_t m_dwCurTickCnt;
	uint32_t m_dwOldTickCnt;

	int64_t m_unSpan;
};

class  CMilliSecTimer
{
public:
	CMilliSecTimer();
	CMilliSecTimer(const CMilliSecTimer & rt);

	CMilliSecTimer & operator = (const CMilliSecTimer & rt);
	void SetSpan(uint32_t dwMilliseconds);
	uint32_t  GetSpan();
	bool IsTrigger();

private:
	//用于计算时间跨度
	uint32_t m_dwInterval;
	uint32_t m_dwCurTickCnt;
	uint32_t m_dwOldTickCnt;


};

