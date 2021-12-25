export module types.Vec;
import <iostream>;
import <type_traits>;
export namespace math {
	enum print_option {
		having_inner_and_is_inner = 0,
		having_inner_but_not_inner = 1,
		is_inner_not_having_inner = 2,
		not_inner_and_not_having_inner = 3
	};
	template<typename Vec>
	using Scalar = std::decay<decltype(Vec()[0])>::type;
	template<typename vec_value>
	concept inner_type_accept = (std::floating_point<vec_value> ||
		std::floating_point<Scalar<vec_value>>) &&
		requires (std::ostream & out, const vec_value & v) {
		out << v;
	};
	template<inner_type_accept vec_value, const int len, const print_option is_inner>
	class BasicVec {
	public:
		BasicVec();
		BasicVec(vec_value fill);
		BasicVec(vec_value values[len]);
		inline BasicVec<vec_value, len, is_inner> operator+(const BasicVec<vec_value, len, is_inner>& rhs) const;
		inline BasicVec<vec_value, len, is_inner> operator-(const BasicVec<vec_value, len, is_inner>& rhs) const;
		inline BasicVec<vec_value, len, is_inner> operator*(const BasicVec<vec_value, len, is_inner>& rhs) const;
		inline BasicVec<vec_value, len, is_inner> operator/(const BasicVec<vec_value, len, is_inner>& rhs) const;
		auto operator[](int i) const->vec_value;
		auto operator[](int i)->vec_value&;
	protected:
		vec_value inner[len];
	};
	template<inner_type_accept vec_value, const int len, const print_option is_inner>
	inline std::ostream& operator<<(std::ostream& out, const BasicVec<vec_value, len, is_inner>& rhs)
	{
		out << "[";
		for (int i = 0; i < len; i++) {
			out << rhs[i];
			if (i != len - 1) {
				out << ",";
				switch (is_inner) {
				case not_inner_and_not_having_inner:
					break;
				case is_inner_not_having_inner:
					break;
				default:
					out << "\n";
				}
			}
			else {
				out << "]";
			}
		}
		return out;
	}
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
		Matrix(vec_value values[col * row]) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					this->inner[i][j] = values[i * col + j];
				}
			}
		}
	};
};
using namespace math;

template<inner_type_accept vec_value, int len, print_option is_inner>
BasicVec<vec_value, len, is_inner>::BasicVec()
{
}

template<inner_type_accept vec_value, int len, print_option is_inner>
BasicVec<vec_value, len, is_inner>::BasicVec(vec_value fill)
{
	for (int i = 0; i < len; i++) {
		inner[i] = fill;
	}
}

template<inner_type_accept vec_value, int len, print_option is_inner>
BasicVec<vec_value, len, is_inner>::BasicVec(vec_value values[len])
{
	for (int i = 0; i < len; i++) {
		this->inner[i] = values[i];
	}
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> BasicVec<vec_value, len, is_inner>::operator+(const BasicVec<vec_value, len, is_inner>& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++) {
		res[i] = this->inner[i] + rhs[i];
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> BasicVec<vec_value, len, is_inner>::operator-(const BasicVec<vec_value, len, is_inner>& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++) {
		res[i] = this->inner[i] - rhs[i];
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> BasicVec<vec_value, len, is_inner>::operator*(const BasicVec<vec_value, len, is_inner>& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++) {
		res[i] = this->inner[i] * rhs[i];
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> BasicVec<vec_value, len, is_inner>::operator/(const BasicVec<vec_value, len, is_inner>& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++) {
		res[i] = this->inner[i] / rhs[i];
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
auto BasicVec<vec_value, len, is_inner>::operator[](int i) const -> vec_value
{
	return inner[i];
}
template<inner_type_accept vec_value, int len, print_option is_inner>
auto BasicVec<vec_value, len, is_inner>::operator[](int i) -> vec_value&
{
	return inner[i];
}