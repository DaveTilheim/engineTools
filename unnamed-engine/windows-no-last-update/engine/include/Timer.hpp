#ifndef TIMER_HPP
#define TIMER_HPP
#include "Dynamic.hpp"
#include "Debug.hpp"
#include <functional>
#include <SFML/System/Clock.hpp>
#include <cstdint>

using namespace std;

class Timer : public Dynamic
{
protected:
	static int timerCounter;
	uint32_t delay = 0.0;
	bool finish = false;
public:
	Timer();
	Timer(uint32_t delay);
	Timer(const Timer& cp);
	virtual ~Timer();
	virtual void update() override = 0;
	uint32_t getDelay() const;
	void setDelay(uint32_t delay);
	bool isFinished() const;
	virtual void restart();
	virtual void terminate();
	Timer& operator=(const Timer& cp);
	friend ostream& operator<<(ostream& out, const Timer& timer);
	static int getTimerCounter();
};

#include <chrono>

class RealtimeTimer : public Timer
{
protected:
	sf::Clock clock;
public:
	RealtimeTimer();
	RealtimeTimer(uint32_t delay);
	RealtimeTimer(const RealtimeTimer& cp);
	virtual ~RealtimeTimer();
	uint32_t getCurrent() const;
	void restart() override;
	void terminate() override;
	RealtimeTimer& operator=(const RealtimeTimer& timer);
	virtual void update() override;
	friend ostream& operator<<(ostream& out, const RealtimeTimer& timer);
};


class FrameTimer : public Timer
{
protected:
	uint32_t frameCount = 0;
public:
	FrameTimer();
	FrameTimer(uint32_t delay);
	FrameTimer(const FrameTimer& cp);
	virtual ~FrameTimer();
	uint32_t getCurrent() const;
	void restart() override;
	void terminate() override;
	FrameTimer& operator=(const FrameTimer& timer);
	virtual void update() override;
	friend ostream& operator<<(ostream& out, const FrameTimer& timer);
};


template <class T=RealtimeTimer> class PeriodicTimer : public T
{
protected:
	unsigned nbPeriod = 0;
public:
	PeriodicTimer();
	PeriodicTimer(uint32_t delay, unsigned nbPeriod=0);
	PeriodicTimer(const PeriodicTimer<T>& cp);
	virtual ~PeriodicTimer();
	PeriodicTimer<T>& operator=(const PeriodicTimer<T>& timer);
	virtual void update() override;
	void setPeriod(unsigned);
};

typedef PeriodicTimer<RealtimeTimer> PeriodicRealtimeTimer;
typedef PeriodicTimer<FrameTimer> PeriodicFrameTimer;


template <class T=RealtimeTimer> class ConditionalPeriodicTimer : public T
{
protected:
	function<bool()> condition;
public:
	ConditionalPeriodicTimer();
	ConditionalPeriodicTimer(uint32_t delay, function<bool()> condition=[](){return false;});
	ConditionalPeriodicTimer(const ConditionalPeriodicTimer<T>& cp);
	virtual ~ConditionalPeriodicTimer();
	ConditionalPeriodicTimer<T>& operator=(const ConditionalPeriodicTimer<T>& timer);
	virtual void update() override;
	void setCondition(function<bool()>);
};

typedef ConditionalPeriodicTimer<RealtimeTimer> ConditionalPeriodicRealtimeTimer;
typedef ConditionalPeriodicTimer<FrameTimer> ConditionalPeriodicFrameTimer;


template <class T=RealtimeTimer> class ContinuousTimer final : public T
{
private:
	function<void()> action = [](){};
public:
	ContinuousTimer();
	ContinuousTimer(uint32_t delay, function<void()> action);
	ContinuousTimer(const ContinuousTimer& cp);
	~ContinuousTimer();
	void update() override;
	ContinuousTimer<T>& operator=(const ContinuousTimer<T>& timer);
};

typedef ContinuousTimer<RealtimeTimer> ContinuousRealtimeTimer;
typedef ContinuousTimer<FrameTimer> ContinuousFrameTimer;

template <class T=RealtimeTimer> class EndTimer final : public T
{
private:
	function<void()> endAction = [](){};
public:
	EndTimer();
	EndTimer(uint32_t delay, function<void()> endAction);
	EndTimer(uint32_t delay, function<void()> endAction, unsigned period); // for periodic
	EndTimer(uint32_t delay, function<void()> endAction, function<bool()> condition); // for conditional periodic
	EndTimer(const EndTimer& cp);
	~EndTimer();
	void update() override;
	EndTimer<T>& operator=(const EndTimer<T>& timer);
};

typedef EndTimer<RealtimeTimer> EndRealtimeTimer;
typedef EndTimer<FrameTimer> EndFrameTimer;
typedef EndTimer<PeriodicTimer<RealtimeTimer>> EndPeriodicRealtimeTimer;
typedef EndTimer<PeriodicTimer<FrameTimer>> EndPeriodicFrameTimer;
typedef EndTimer<ConditionalPeriodicTimer<RealtimeTimer>> EndConditionalPeriodicRealtimeTimer;
typedef EndTimer<ConditionalPeriodicTimer<FrameTimer>> EndConditionalPeriodicFrameTimer;

template <class T=RealtimeTimer> class ContinuousEndTimer final : public T
{
private:
	function<void()> action;
	function<void()> endAction;
public:
	ContinuousEndTimer();
	ContinuousEndTimer(uint32_t delay, function<void()> action, function<void()> endAction);
	ContinuousEndTimer(uint32_t delay, function<void()> action, function<void()> endAction, unsigned period);
	ContinuousEndTimer(uint32_t delay, function<void()> action, function<void()> endAction, function<bool()> condition);
	ContinuousEndTimer(const ContinuousEndTimer& cp);
	~ContinuousEndTimer();
	void update() override;
	ContinuousEndTimer<T>& operator=(const ContinuousEndTimer<T>& timer);
};

typedef ContinuousEndTimer<RealtimeTimer> ContinuousEndRealtimeTimer;
typedef ContinuousEndTimer<FrameTimer> ContinuousEndFrameTimer;
typedef ContinuousEndTimer<PeriodicTimer<RealtimeTimer>> ContinuousEndPeriodicRealtimeTimer;
typedef ContinuousEndTimer<PeriodicTimer<FrameTimer>> ContinuousEndPeriodicFrameTimer;
typedef ContinuousEndTimer<ConditionalPeriodicTimer<RealtimeTimer>> ContinuousEndConditionalPeriodicRealtimeTimer;
typedef ContinuousEndTimer<ConditionalPeriodicTimer<FrameTimer>> ContinuousEndConditionalPeriodicFrameTimer;

typedef RealtimeTimer R_Timer;
typedef FrameTimer F_Timer;
typedef PeriodicRealtimeTimer PR_Timer;
typedef PeriodicFrameTimer PF_Timer;
typedef ConditionalPeriodicRealtimeTimer CPR_Timer;
typedef ConditionalPeriodicFrameTimer CPF_Timer;
typedef ContinuousRealtimeTimer CR_Timer;
typedef ContinuousFrameTimer CF_Timer;
typedef EndRealtimeTimer ER_Timer;
typedef EndFrameTimer EF_Timer;
typedef EndPeriodicRealtimeTimer EPR_Timer;
typedef EndPeriodicFrameTimer EPF_Timer;
typedef EndConditionalPeriodicRealtimeTimer ECPR_Timer;
typedef EndConditionalPeriodicFrameTimer ECPF_Timer;
typedef ContinuousEndRealtimeTimer CER_Timer;
typedef ContinuousEndFrameTimer CEF_Timer;
typedef ContinuousEndPeriodicRealtimeTimer CEPR_Timer;
typedef ContinuousEndPeriodicFrameTimer CEPF_Timer;
typedef ContinuousEndConditionalPeriodicRealtimeTimer CECPR_Timer;
typedef ContinuousEndConditionalPeriodicFrameTimer CECPF_Timer;


inline uint32_t ms(float sec)
{
	return sec * 1000;
}


#endif
