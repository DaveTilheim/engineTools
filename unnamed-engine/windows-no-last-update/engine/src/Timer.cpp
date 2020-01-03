#include "Timer.hpp"


int Timer::timerCounter = 0;


Timer::Timer() : Dynamic(false)
{
	timerCounter++;
	trace("Timer creation");
}

Timer::Timer(uint32_t delay) : Dynamic(), delay(delay)
{
	timerCounter++;
	trace("Timer creation");
}

Timer::Timer(const Timer& cp) : Dynamic(cp), delay(cp.getDelay())
{
	timerCounter++;
	trace("Timer creation");
}

Timer::~Timer()
{
	timerCounter--;
	trace("Timer destruction");
}

uint32_t Timer::getDelay() const
{
	return delay;
}

void Timer::setDelay(uint32_t delay_)
{
	delay = delay_;
}

bool Timer::isFinished() const
{
	return finish;
}

void Timer::restart()
{
	finish = false;
}

void Timer::terminate()
{
	finish = true;
}

Timer& Timer::operator=(const Timer& cp)
{
	Dynamic::operator=(cp);
	setDelay(cp.getDelay());
	finish = cp.finish;
	return *this;
}

ostream& operator<<(ostream& out, const Timer& timer)
{
	out << "Delay: " << timer.delay << "\tFinish: " << timer.finish;
	return out;
}

int Timer::getTimerCounter()
{
	return Timer::timerCounter;
}



RealtimeTimer::RealtimeTimer() : Timer()
{
	trace("RealtimeTimer creation");
}

RealtimeTimer::RealtimeTimer(uint32_t delay) : Timer(delay)
{
	trace("RealtimeTimer creation");
}

RealtimeTimer::RealtimeTimer(const RealtimeTimer& cp) : Timer(cp.getDelay())
{
	trace("RealtimeTimer creation");
}

RealtimeTimer::~RealtimeTimer()
{
	trace("RealtimeTimer destruction");
}

RealtimeTimer& RealtimeTimer::operator=(const RealtimeTimer& timer)
{
	Timer::operator=(timer);
	return *this;
}

void RealtimeTimer::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
		}
	}
}

uint32_t RealtimeTimer::getCurrent() const
{
	return (uint32_t)clock.getElapsedTime().asMilliseconds();
}

void RealtimeTimer::restart()
{
	Timer::restart();
	clock.restart();
}

void RealtimeTimer::terminate()
{
	Timer::terminate();
	clock.restart();
}

ostream& operator<<(ostream& out, const RealtimeTimer& timer)
{
	out << *dynamic_cast<const Timer *>(&timer) << " Current: " << timer.getCurrent();
	return out;
}



FrameTimer::FrameTimer() : Timer()
{
	trace("FrameTimer creation");
}

FrameTimer::FrameTimer(uint32_t delay) : Timer(delay)
{
	trace("FrameTimer creation");
}

FrameTimer::FrameTimer(const FrameTimer& cp) : Timer(cp.getDelay())
{
	trace("FrameTimer creation");
}

FrameTimer::~FrameTimer()
{
	trace("FrameTimer destruction");
}

FrameTimer& FrameTimer::operator=(const FrameTimer& timer)
{
	Timer::operator=(timer);
	frameCount = timer.frameCount;
	return *this;
}

void FrameTimer::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
		}
	}
}

uint32_t FrameTimer::getCurrent() const
{
	return frameCount;
}

void FrameTimer::restart()
{
	Timer::restart();
	frameCount = 0;
}

void FrameTimer::terminate()
{
	Timer::terminate();
	frameCount = 0;
}

ostream& operator<<(ostream& out, const FrameTimer& timer)
{
	out << *dynamic_cast<const Timer *>(&timer) << " Frame: " << timer.frameCount;
	return out;
}


template <class T> PeriodicTimer<T>::PeriodicTimer() : T()
{
	trace("PeriodicTimer creation");
}

template <class T> PeriodicTimer<T>::PeriodicTimer(uint32_t delay, unsigned nbPeriod) : T(delay), nbPeriod(nbPeriod)
{
	trace("PeriodicTimer creation");
}

template <class T> PeriodicTimer<T>::PeriodicTimer(const PeriodicTimer<T>& cp) : T(cp), nbPeriod(cp.nbPeriod)
{
	trace("PeriodicTimer creation");
}

template <class T> PeriodicTimer<T>::~PeriodicTimer()
{
	trace("PeriodicTimer destruction");
}

template <class T> PeriodicTimer<T>& PeriodicTimer<T>::operator=(const PeriodicTimer<T>& timer)
{
	T::operator=(timer);
	nbPeriod = timer.nbPeriod;
	return *this;
}


template <> void PeriodicTimer<RealtimeTimer>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			if(nbPeriod)
			{
				restart();
				nbPeriod--;
			}
		}
	}
}

template <> void PeriodicTimer<FrameTimer>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			if(nbPeriod)
			{
				restart();
				nbPeriod--;
			}
		}
	}
}

template <class T> void PeriodicTimer<T>::setPeriod(unsigned period)
{
	nbPeriod = period;
}

template class PeriodicTimer<RealtimeTimer>;
template class PeriodicTimer<FrameTimer>;





template <class T> ConditionalPeriodicTimer<T>::ConditionalPeriodicTimer() : T()
{
	trace("ConditionalPeriodicTimer creation");
}

template <class T> ConditionalPeriodicTimer<T>::ConditionalPeriodicTimer(uint32_t delay, function<bool()> c) : T(delay), condition(c)
{
	trace("ConditionalPeriodicTimer creation");
}

template <class T> ConditionalPeriodicTimer<T>::ConditionalPeriodicTimer(const ConditionalPeriodicTimer<T>& cp) : T(cp), condition(cp.condition)
{
	trace("ConditionalPeriodicTimer creation");
}

template <class T> ConditionalPeriodicTimer<T>::~ConditionalPeriodicTimer()
{
	trace("ConditionalPeriodicTimer destruction");
}

template <class T> ConditionalPeriodicTimer<T>& ConditionalPeriodicTimer<T>::operator=(const ConditionalPeriodicTimer<T>& timer)
{
	T::operator=(timer);
	condition = timer.condition;
	return *this;
}


template <> void ConditionalPeriodicTimer<RealtimeTimer>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			if(condition())
			{
				restart();
			}
		}
	}
}

template <> void ConditionalPeriodicTimer<FrameTimer>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			if(condition())
			{
				restart();
			}
		}
	}
}

template <class T> void ConditionalPeriodicTimer<T>::setCondition(function<bool()> c)
{
	condition = c;
}

template class ConditionalPeriodicTimer<RealtimeTimer>;
template class ConditionalPeriodicTimer<FrameTimer>;





template <class T> ContinuousTimer<T>::ContinuousTimer() : T()
{
	trace("ContinuousTimer creation");
}

template <class T> ContinuousTimer<T>::ContinuousTimer(uint32_t delay, function<void()> action) : T(delay), action(action)
{
	trace("ContinuousTimer creation");
}

template <class T> ContinuousTimer<T>::ContinuousTimer(const ContinuousTimer& cp) : T(cp), action(cp.action)
{
	trace("ContinuousTimer creation");
}

template <class T> ContinuousTimer<T>::~ContinuousTimer()
{
	trace("ContinuousTimer destruction");
}

template <> void ContinuousTimer<RealtimeTimer>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
		}
		else
		{
			action();
		}
	}
}

template <> void ContinuousTimer<FrameTimer>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
		}
		else
		{
			action();
		}
	}
}

template <class T> ContinuousTimer<T>& ContinuousTimer<T>::operator=(const ContinuousTimer<T>& timer)
{
	T::operator=(timer);
	action = timer.action;
	return *this;
}

template class ContinuousTimer<RealtimeTimer>;
template class ContinuousTimer<FrameTimer>;





template <class T> EndTimer<T>::EndTimer() : T()
{
	trace("EndTimer creation");
}

template <class T> EndTimer<T>::EndTimer(uint32_t delay, function<void()> action) : T(delay), endAction(action)
{
	trace("EndTimer creation");
}

template <class T> EndTimer<T>::EndTimer(uint32_t delay, function<void()> action, unsigned period) : T(delay), endAction(action)
{
	if(dynamic_cast<PeriodicTimer<RealtimeTimer> *>(this))
	{
		dynamic_cast<PeriodicTimer<RealtimeTimer> *>(this)->setPeriod(period);
	}
	else if(dynamic_cast<PeriodicTimer<FrameTimer> *>(this))
	{
		dynamic_cast<PeriodicTimer<FrameTimer> *>(this)->setPeriod(period);
	}
	trace("EndTimer creation");
}

template <class T> EndTimer<T>::EndTimer(uint32_t delay, function<void()> action, function<bool()> condition) : T(delay), endAction(action)
{
	if(dynamic_cast<ConditionalPeriodicTimer<RealtimeTimer> *>(this))
	{
		dynamic_cast<ConditionalPeriodicTimer<RealtimeTimer> *>(this)->setCondition(condition);
	}
	else if(dynamic_cast<ConditionalPeriodicTimer<FrameTimer> *>(this))
	{
		dynamic_cast<ConditionalPeriodicTimer<FrameTimer> *>(this)->setCondition(condition);
	}
	trace("EndTimer creation");
}

template <class T> EndTimer<T>::EndTimer(const EndTimer& cp) : T(cp), endAction(cp.endAction)
{
	trace("EndTimer creation");
}

template <class T> EndTimer<T>::~EndTimer()
{
	trace("EndTimer destruction");
}

template <> void EndTimer<RealtimeTimer>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			endAction();
		}
	}
}

template <> void EndTimer<FrameTimer>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			endAction();
		}
	}
}

template <> void EndTimer<PeriodicTimer<RealtimeTimer>>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			endAction();
			if(nbPeriod)
			{
				restart();
				nbPeriod--;
			}
		}
	}
}

template <> void EndTimer<PeriodicTimer<FrameTimer>>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			endAction();
			if(nbPeriod)
			{
				restart();
				nbPeriod--;
			}
		}
	}
}

template <> void EndTimer<ConditionalPeriodicTimer<RealtimeTimer>>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			endAction();
			if(condition())
			{
				restart();
			}
		}
	}
}

template <> void EndTimer<ConditionalPeriodicTimer<FrameTimer>>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			endAction();
			if(condition())
			{
				restart();
			}
		}
	}
}

template <class T> EndTimer<T>& EndTimer<T>::operator=(const EndTimer<T>& timer)
{
	T::operator=(timer);
	endAction = timer.endAction;
	return *this;
}

template class EndTimer<RealtimeTimer>;
template class EndTimer<FrameTimer>;
template class EndTimer<PeriodicTimer<RealtimeTimer>>;
template class EndTimer<PeriodicTimer<FrameTimer>>;
template class EndTimer<ConditionalPeriodicTimer<RealtimeTimer>>;
template class EndTimer<ConditionalPeriodicTimer<FrameTimer>>;





template <class T> ContinuousEndTimer<T>::ContinuousEndTimer() : T()
{
	trace("ContinuousEndTimer creation");
}

template <class T> ContinuousEndTimer<T>::ContinuousEndTimer(uint32_t delay, function<void()> action, function<void()> endAction) : T(delay),
action(action), endAction(endAction)
{
	trace("ContinuousEndTimer creation");
}

template <class T> ContinuousEndTimer<T>::ContinuousEndTimer(uint32_t delay, function<void()> action, function<void()> endAction, unsigned period) : T(delay),
action(action), endAction(endAction)
{
	if(dynamic_cast<PeriodicTimer<RealtimeTimer> *>(this))
	{
		dynamic_cast<PeriodicTimer<RealtimeTimer> *>(this)->setPeriod(period);
	}
	else if(dynamic_cast<PeriodicTimer<FrameTimer> *>(this))
	{
		dynamic_cast<PeriodicTimer<FrameTimer> *>(this)->setPeriod(period);
	}
	trace("ContinuousEndTimer creation");
}

template <class T> ContinuousEndTimer<T>::ContinuousEndTimer(uint32_t delay, function<void()> action, function<void()> endAction, function<bool()> condition) : T(delay),
action(action), endAction(endAction)
{
	if(dynamic_cast<ConditionalPeriodicTimer<RealtimeTimer> *>(this))
	{
		dynamic_cast<ConditionalPeriodicTimer<RealtimeTimer> *>(this)->setCondition(condition);
	}
	else if(dynamic_cast<ConditionalPeriodicTimer<FrameTimer> *>(this))
	{
		dynamic_cast<ConditionalPeriodicTimer<FrameTimer> *>(this)->setCondition(condition);
	}
	trace("ContinuousEndTimer creation");
}

template <class T> ContinuousEndTimer<T>::ContinuousEndTimer(const ContinuousEndTimer& cp) : T(cp), action(cp.action), endAction(cp.endAction)
{
	trace("ContinuousEndTimer creation");
}

template <class T> ContinuousEndTimer<T>::~ContinuousEndTimer()
{
	trace("ContinuousEndTimer destruction");
}

template <> void ContinuousEndTimer<RealtimeTimer>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			endAction();
		}
		else
		{
			action();
		}
	}
}

template <> void ContinuousEndTimer<FrameTimer>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			endAction();
		}
		else
		{
			action();
		}
	}
}

template <> void ContinuousEndTimer<PeriodicTimer<RealtimeTimer>>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			endAction();
			if(nbPeriod)
			{
				restart();
				nbPeriod--;
			}
		}
		else
		{
			action();
		}
	}
}

template <> void ContinuousEndTimer<PeriodicTimer<FrameTimer>>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			endAction();
			if(nbPeriod)
			{
				restart();
				nbPeriod--;
			}
		}
		else
		{
			action();
		}
	}
}

template <> void ContinuousEndTimer<ConditionalPeriodicTimer<RealtimeTimer>>::update()
{
	if(not finish)
	{
		if((uint32_t)clock.getElapsedTime().asMilliseconds() >= delay)
		{
			finish = true;
			endAction();
			if(condition())
			{
				restart();
			}
		}
		else
		{
			action();
		}
	}
}

template <> void ContinuousEndTimer<ConditionalPeriodicTimer<FrameTimer>>::update()
{
	if(not finish)
	{
		frameCount++;
		if(frameCount >= delay)
		{
			finish = true;
			endAction();
			if(condition())
			{
				restart();
			}
		}
		else
		{
			action();
		}
	}
}

template <class T> ContinuousEndTimer<T>& ContinuousEndTimer<T>::operator=(const ContinuousEndTimer<T>& timer)
{
	T::operator=(timer);
	action = timer.action;
	endAction = timer.endAction;
	return *this;
}

template class ContinuousEndTimer<RealtimeTimer>;
template class ContinuousEndTimer<FrameTimer>;
template class ContinuousEndTimer<PeriodicTimer<RealtimeTimer>>;
template class ContinuousEndTimer<PeriodicTimer<FrameTimer>>;
template class ContinuousEndTimer<ConditionalPeriodicTimer<RealtimeTimer>>;
template class ContinuousEndTimer<ConditionalPeriodicTimer<FrameTimer>>;
