#pragma once
#include <stdint.h>
#include <memory>


class TimingData {
public:
	TimingData(const TimingData&) = delete;
	TimingData& operator=(const TimingData&) = delete;

	static TimingData& Get();
	static void Update();
	static void Init();
	static void DeInit();
	static uint64_t GetTime();
	static uint64_t GetClock();


	uint32_t m_FrameNumber;
	uint64_t m_LastFrameTimeStamp;
	uint64_t m_LastFrameDuration;
	uint64_t m_LastFrameClockStamp;
	uint64_t m_LastFrameClockTicks;

	bool m_IsPaused;
	float m_AverageFrameDuration;
	float m_FPS;

private:
	TimingData() = default;
	//static TimingData* timing_data;

};