/**
 * @file PerlinNoise.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

/**
 * @brief Implementacja szumu perlina
 */
class PerlinNoise {
private:

	[[nodiscard]] double total(double i, double j) const;
	[[nodiscard]] double getValue(double x, double y) const;
	[[nodiscard]] double interpolate(double x, double y, double a) const;
	[[nodiscard]] double noise(int x, int y) const;

	double persistence, frequency, amplitude;
	int octaves, randomseed;
public:

	PerlinNoise();
	PerlinNoise(double _persistence, double _frequency,
				double _amplitude, int _octaves, int _randomseed);

	[[nodiscard]] double getHeight(double x, double y) const;

	[[nodiscard]] double getPersistence() const;
	[[nodiscard]] double getFrequency() const;
	[[nodiscard]] double getAmplitude() const;
	[[nodiscard]] int getOctaves() const;
	[[nodiscard]] int getRandomSeed() const;

	void set(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);

	void setPersistence(double _persistence);
	void setFrequency(double _frequency);
	void setAmplitude(double _amplitude);
	void setOctaves(int _octaves);
	void setRandomSeed(int _randomseed);
};