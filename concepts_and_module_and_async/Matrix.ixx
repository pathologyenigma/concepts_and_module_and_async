export module math.Matrix;
import math.Vec;
export namespace math {
	template<inner_type_accept vec_value, const int col, const int row>
	class Matrix : public BasicVec<BasicVec<vec_value, col, is_inner_not_having_inner>, row, having_inner_but_not_inner>
	{
	public:
		Matrix();
		Matrix(vec_value fill) {
			for (int i = 0; i < col; i++) {
				for (int j = 0; j < row; j++) {
					this->inner[i][j] = fill;
				}
			}
		}
		Matrix(std::initializer_list<vec_value> values) {
			for (size_t i = 0; i < row; i++) {
				for (size_t j = 0; j < col; j++) {
					auto index = i * col + j;
					if (index < values.size())
						this->inner[i][j] = values[i * col + j];
					else return;
				}
			}
		}
	};
};