export module math.Utils;

export namespace math {
	double sqrt(double x) {
		float	y;
		float	delta;
		float	maxError;

		if (x <= 0) {
			return 0;
		}

		// initial guess
		y = x / 2;

		// refine
		maxError = x * 0.001;

		do {
			delta = (y * y) - x;
			y -= delta / (2 * y);
		} while (delta > maxError || delta < -maxError);

		return y;
	}
};