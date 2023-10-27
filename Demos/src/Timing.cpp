#include "Timing.h"
#include <chrono>
#include <memory>


static TimingData* timing_data;

TimingData& TimingData::Get() {
	return *timing_data;
}

void TimingData::Update() {
	if (!timing_data) {
		return;
	}

	if (!timing_data->m_IsPaused) {
		++timing_data->m_FrameNumber;
	}

	uint64_t current_time = GetTime();
	timing_data->m_LastFrameDuration = current_time - timing_data->m_LastFrameTimeStamp;
	timing_data->m_LastFrameTimeStamp = current_time;

	uint64_t current_clock = GetClock();
	timing_data->m_LastFrameClockTicks = current_clock - timing_data->m_LastFrameClockTicks;

	timing_data->m_LastFrameClockTicks = current_clock;

	if (timing_data->m_FrameNumber > 1) {
		if (timing_data->m_AverageFrameDuration <= 0.0f) {
			timing_data->m_AverageFrameDuration = static_cast<float>(timing_data->m_LastFrameDuration);
		}
		else {
			timing_data->m_AverageFrameDuration *= 0.99f;
			timing_data->m_AverageFrameDuration += 0.01f * static_cast<float>(timing_data->m_LastFrameDuration);

			timing_data->m_FPS = 1000.0f / timing_data->m_AverageFrameDuration;
		}
	}
}

void TimingData::Init() {
	if (!timing_data) {
		timing_data = new TimingData();
	}

	timing_data->m_FrameNumber = 0;

	timing_data->m_LastFrameTimeStamp = GetTime();
	timing_data->m_LastFrameDuration = 0;

	timing_data->m_LastFrameClockStamp = GetClock();
	timing_data->m_LastFrameClockTicks = 0;

	timing_data->m_IsPaused = false;

	timing_data->m_AverageFrameDuration = 0.0f;
	timing_data->m_FPS = 0;
}


void TimingData::DeInit() {
	delete timing_data;
	timing_data = nullptr;
}

uint64_t TimingData::GetTime() {
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	return ms.time_since_epoch().count();
}

uint64_t TimingData::GetClock() {
	auto now = std::chrono::system_clock::now();
	return now.time_since_epoch().count();
}

