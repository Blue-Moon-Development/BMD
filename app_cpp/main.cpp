/*
 * BMD
 * Copyright (C) 2020 Blue Moon Development. All rights reserved.
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * Contact: team@bluemoondev.org
 * 
 * File Name: main.cpp
 * Date File Created: 8/10/2020 at 7:16 PM
 * Author: Matt
 */

#define BMD_HEADERS_ONLY
#define BMD_DEBUGGING 0
#define BMD_PROFILE 1

#include <bmd/core.h>


float xPos = 0;
float velX = 0;

void update(float delta, float tt)
{
	velX = 2.0f * delta;
	xPos += velX;
	if (xPos >= 20)
	{
		//fprintf(stderr, "Xpos hit a wall!\n");
		xPos = 20;
		velX = 0;
	}
	//printf("UPDATE XPOS: %f (time: %f)\n", xPos, tt);
}

void render(float interpolation, float tt)
{
	float x = xPos + (velX * interpolation);
	//printf("RENDER XPOS: %f (farseer: %f)  Rendering xpos at %f  (time: %f)\n", xPos, interpolation,
	//	   x, tt);

}

void calculateFps(int& running, float& elapsed, int& ticks)
{
	static int frames;
	frames++;

	if (elapsed >= 1.0f)
	{
		float mspf = 1000.0f / (float) frames;
		printf("FPS: %i -- mspf: %f  --- ticks: %i\n", frames, mspf, ticks);
		frames = 0;
		elapsed = 0;
		ticks = 0;
		running++;
	}
}


// Fixed update time step, variable rendering
void gameloop1()
{
	float dt = 1.0f / 120.0f;
	int maxSkip = 10;
	timer_t timer;
	initTimer(&timer);
	int running = 0;
	float accumulatedTime = 0;
	int loops = 0;
	float ft = 0;
	int ticks = 0;
	printf("Starting at second: %lli\n", seconds(&timer, timer.startTime));
	while (running < 10)
	{
		tickTimer(&timer);

		if(ft >= 1.0f)
		{
			printf("Xpos at %f\n", xPos);
			printf("Seconds: %lli\n", seconds(&timer, timer.currentTime));
			printf("Milliseconds: %lli\n", milliseconds(&timer, timer.currentTime));
			printf("Microseconds: %lli\n", microseconds(&timer, timer.currentTime));
		}
		calculateFps(running, ft, ticks);

		accumulatedTime += timer.delta;
		ft += timer.delta;
		loops = 0;
		//printf("Accum: %f\n", accumulatedTime);

		// Process input

		while (accumulatedTime >= dt && loops < maxSkip)
		{
			ticks++;
			update(dt, totalTime(&timer));
			accumulatedTime -= dt;
			loops++;
		}

		render(accumulatedTime / dt, totalTime(&timer));
	}
}

float xPos2 = 0;
float velX2 = 0;
void update(float delta)
{
	velX2 = 2.0f * delta;
	xPos2 += velX2;
	//if (xPos2 >= 20)
	//{
	//	//fprintf(stderr, "Xpos hit a wall!\n");
	//	xPos2 = 20;
	//	velX2 = 0;
	//}
}

void render()
{
	//printf("Rendering xpos2 at %f\n, xPos2);
}


// Variable time step
void gameloop2()
{
	timer_t timer;
	initTimer(&timer);
	int running = 0;
	float ft = 0;
	int ticks = 0;
	while (running < 10)
	{
		tickTimer(&timer);

		if(ft >= 1.0f)
		{
			printf("Xpos is at %f\n", xPos2);
		}

		calculateFps(running, ft, ticks);

		ft += timer.delta;
		//printf("Accum: %f\n", accumulatedTime);

		// Process input

		update(timer.delta);
		ticks++;
		render();
	}
}

int main(int argc, char** argv)
{
	PROFILER_SCOPE(1);
	PROFILER_WRAP(gameloop1);
	//gameloop2();

	PROFILER_WRAP(initLog, "./info.log", LOG_MODE_OVERWRITE, 5);
	//initLog("./info.log", LOG_MODE_OVERWRITE, 5);
	PROFILER_START("Profiler logs");
	logInfo("test");
	logInfo("test");
	logInfo("test");
	logInfo("test");
	logInfo("test");
	logInfo("test");
	logInfo("test");
	logInfo("test");
	logInfo("test");
	PROFILER_END;

	{
		PROFILER_SCOPE(2);
		logWarn("test scope");
		logWarn("test scope");
		logWarn("test scope");
		logWarn("test scope");
	}

	return 0;
}

