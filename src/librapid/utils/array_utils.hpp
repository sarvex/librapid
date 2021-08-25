#ifndef LIBRAPID_ARRAY_UTILS
#define LIBRAPID_ARRAY_UTILS

#include <librapid/config.hpp>
#include <librapid/autocast/autocast.hpp>

namespace librapid
{
	namespace imp
	{
		/**
		 * \rst
		 *
		 * Calculate the number of digits before and after the decimal point
		 * of a number. If the number is an integer, there are zero digits after
		 * the decimal point.
		 *
		 * For example, the number :math:`3.141` has one digit before the decimal
		 * point, and three digits after it.
		 *
		 * \endrst
		 */
		template<typename A, typename B>
		inline void autocastBeforeAfterDecimal(const Accelerator &locnA,
											   const Accelerator &locnB,
											   A *__restrict data, B *,
											   std::pair<lr_int, lr_int> &res)
		{
			std::stringstream stream;
			stream.precision(10);

			stream << std::boolalpha;

			if (locnA == Accelerator::CPU)
			{
				stream << *data;
			}
		#ifdef LIBRAPID_HAS_CUDA
			else
			{
				auto tmp = (A *) malloc(sizeof(A));

			#ifdef LIBRAPID_CUDA_STREAM
				cudaSafeCall(cudaMemcpyAsync(tmp, data, sizeof(A),
							 cudaMemcpyDeviceToHost, cudaStream));
			#else
				cudaSafeCall(cudaMemcpy(tmp, data, sizeof(A), cudaMemcpyDeviceToHost));
			#endif // LIBRAPID_CUDA_STREAM

				stream << *tmp;
				free(tmp);
			}
		#endif

			std::string str = stream.str();
			if (std::is_floating_point<A>::value &&
				str.find_last_of('.') == std::string::npos)
			{
				res = {str.length(), 0};
				return;
			}

			size_t index = str.find_last_of('.');
			if (index == std::string::npos)
			{
				res = {str.length(), 0};
				return;
			}

			res = {index, str.length() - index - 1};
		}

		template<typename A, typename B>
		inline void autocastFormatValue(const Accelerator &locnA,
										const Accelerator &locnB,
										A *__restrict data, B *,
										std::string &res)
		{
			std::stringstream stream;
			stream.precision(10);

			stream << std::boolalpha;

			if (locnA == Accelerator::CPU)
			{
				stream << *data;
			}
		#ifdef LIBRAPID_HAS_CUDA
			else
			{
				auto tmp = (A *) malloc(sizeof(A));

			#ifdef LIBRAPID_CUDA_STREAM
				cudaSafeCall(cudaMemcpyAsync(tmp, data, sizeof(A),
							 cudaMemcpyDeviceToHost, cudaStream));
			#else
				cudaSafeCall(cudaMemcpy(tmp, data, sizeof(A), cudaMemcpyDeviceToHost));
			#endif // LIBRAPID_CUDA_STREAM

				stream << *tmp;
				free(tmp);
			}
		#endif

			res = stream.str();
			if (std::is_floating_point<A>::value &&
				res.find_last_of('.') == std::string::npos)
				res += ".";
		}
	}
}

#endif // LIBRAPID_ARRAY_UTILS