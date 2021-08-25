#ifndef LIBRAPID_OPS
#define LIBRAPID_OPS

#include <librapid/config.hpp>
#include <librapid/math/rapid_math.hpp>
#include <librapid/array/extent.hpp>
#include <librapid/array/stride.hpp>
#include <librapid/autocast/autocast.hpp>

namespace librapid
{
	namespace ops
	{
		struct Add
		{
			const char *name = "add";
			const char *kernel = R"V0G0N(
					unsigned int tid = blockDim.x * blockIdx.x + threadIdx.x;
					if (tid < size) c[tid] = a[tid] + b[tid];
				)V0G0N";

			template<typename A, typename B>
			inline auto operator()(A a, B b) const
			{
				return a + b;
			}
		};

		struct Sub
		{
			const char *name = "add";
			const char *kernel = R"V0G0N(
					unsigned int tid = blockDim.x * blockIdx.x + threadIdx.x;
					if (tid < size) c[tid] = a[tid] - b[tid];
				)V0G0N";

			template<typename A, typename B>
			inline auto operator()(A a, B b) const
			{
				return a - b;
			}
		};
	}
}

#endif // LIBRAPID_OPS