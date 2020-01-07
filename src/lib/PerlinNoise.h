/**
 * @file PerlinNoise.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

class PerlinNoise {
private:

	double total(double i, double j) const;
	double getValue(double x, double y) const;
	double interpolate(double x, double y, double a) const;
	double noise(int x, int y) const;

	double persistence, frequency, amplitude;
	int octaves, randomseed;
public:

	PerlinNoise();
	PerlinNoise(double _persistence, double _frequency,
				double _amplitude, int _octaves, int _randomseed);

	double getHeight(double x, double y) const;

	double getPersistence() const;
	double getFrequency() const;
	double getAmplitude() const;
	int getOctaves() const;
	int getRandomSeed() const;

	void set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);

	void setPersistence(double _persistence);
	void setFrequency(double _frequency);
	void setAmplitude(double _amplitude);
	void setOctaves(int _octaves);
	void setRandomSeed(int _randomseed);
};