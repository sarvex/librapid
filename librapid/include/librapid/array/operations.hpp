#ifndef LIBRAPID_ARRAY_OPERATIONS_HPP
#define LIBRAPID_ARRAY_OPERATIONS_HPP

#define LIBRAPID_BINARY_FUNCTOR(NAME_, OP_)                                                        \
	struct NAME_ {                                                                                 \
		template<typename T, typename V>                                                           \
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto operator()(const T &lhs,                    \
																  const V &rhs) const {            \
			return lhs OP_ rhs;                                                                    \
		}                                                                                          \
                                                                                                   \
		template<typename Packet>                                                                  \
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto packet(const Packet &lhs,                   \
															  const Packet &rhs) const {           \
			return lhs OP_ rhs;                                                                    \
		}                                                                                          \
	}

#define LIBRAPID_BINARY_COMPARISON_FUNCTOR(NAME_, OP_)                                             \
	struct NAME_ {                                                                                 \
		template<typename T, typename V>                                                           \
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto operator()(const T &lhs,                    \
																  const V &rhs) const {            \
			return (typename std::common_type_t<T, V>)(lhs OP_ rhs);                               \
		}                                                                                          \
                                                                                                   \
		template<typename Packet>                                                                  \
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto packet(const Packet &lhs,                   \
															  const Packet &rhs) const {           \
			auto mask = lhs OP_ rhs;                                                               \
			Packet res(1);                                                                         \
			res.setZero(!mask);                                                                    \
			return res;                                                                            \
		}                                                                                          \
	}

namespace librapid {
	namespace detail {
		template<typename desc, typename Functor, typename... Args>
		auto makeFunction(Args &&...args) {
			using OperationType = Function<desc, Functor, Args...>;
			return OperationType(Functor(), std::forward<Args>(args)...);
		}

		LIBRAPID_BINARY_FUNCTOR(Plus, +);	  // a + b
		LIBRAPID_BINARY_FUNCTOR(Minus, -);	  // a - b
		LIBRAPID_BINARY_FUNCTOR(Multiply, *); // a * b
		LIBRAPID_BINARY_FUNCTOR(Divide, /);	  // a / b

		LIBRAPID_BINARY_COMPARISON_FUNCTOR(LessThan, <);			 // a < b
		LIBRAPID_BINARY_COMPARISON_FUNCTOR(GreaterThan, >);			 // a > b
		LIBRAPID_BINARY_COMPARISON_FUNCTOR(LessThanEqual, <=);		 // a <= b
		LIBRAPID_BINARY_COMPARISON_FUNCTOR(GreaterThanEqual, >=);	 // a >= b
		LIBRAPID_BINARY_COMPARISON_FUNCTOR(ElementWiseEqual, ==);	 // a == b
		LIBRAPID_BINARY_COMPARISON_FUNCTOR(ElementWiseNotEqual, !=); // a != b

	} // namespace detail

	namespace typetraits {
		template<typename Descriptor1, typename Descriptor2>
		struct DescriptorMerger {
			using Type = ::librapid::detail::descriptor::Combined;
		};

		template<typename Descriptor1>
		struct DescriptorMerger<Descriptor1, Descriptor1> {
			using Type = Descriptor1;
		};

		template<typename T>
		struct DescriptorExtractor {
			using Type = T;
		};

		template<typename ShapeType, typename StorageType>
		struct DescriptorExtractor<array::ArrayContainer<ShapeType, StorageType>> {
			using Type = ::librapid::detail::descriptor::Trivial;
		};

		template<typename Descriptor, typename Functor, typename... Args>
		struct DescriptorExtractor<::librapid::detail::Function<Descriptor, Functor, Args...>> {
			using Type = Descriptor;
		};

		template<typename First, typename... Rest>
		struct DescriptorType;

		namespace impl {
			template<typename... Rest>
			constexpr auto descriptorExtractor() {
				if constexpr (sizeof...(Rest) > 0) {
					using ReturnType = typename DescriptorType<Rest...>::Type;
					return ReturnType {};
				} else {
					using ReturnType = ::librapid::detail::descriptor::Trivial;
					return ReturnType {};
				}
			}
		} // namespace impl

		template<typename First, typename... Rest>
		struct DescriptorType {
			using FirstType		  = std::decay_t<First>;
			using FirstDescriptor = typename DescriptorExtractor<FirstType>::Type;
			using RestDescriptor  = decltype(impl::descriptorExtractor<Rest...>());

			using Type = typename DescriptorMerger<FirstDescriptor, RestDescriptor>::Type;
		};

		template<typename... Args>
		using DescriptorType_t = typename DescriptorType<Args...>::Type;

		template<>
		struct TypeInfo<::librapid::detail::Plus> {
			static constexpr const char *name		= "plus";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "addArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::Minus> {
			static constexpr const char *name		= "minus";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "subArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::Multiply> {
			static constexpr const char *name		= "multiply";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "mulArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::Divide> {
			static constexpr const char *name		= "divide";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "divArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::LessThan> {
			static constexpr const char *name		= "less than";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "lessThanArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::GreaterThan> {
			static constexpr const char *name		= "greater than";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "greaterThanArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::LessThanEqual> {
			static constexpr const char *name		= "less than or equal";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "lessThanEqualArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::GreaterThanEqual> {
			static constexpr const char *name		= "greater than or equal";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "greaterThanEqualArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::ElementWiseEqual> {
			static constexpr const char *name		= "element wise equal";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "elementWiseEqualArrays";
		};

		template<>
		struct TypeInfo<::librapid::detail::ElementWiseNotEqual> {
			static constexpr const char *name		= "element wise not equal";
			static constexpr const char *filename	= "arithmetic";
			static constexpr const char *kernelName = "elementWiseNotEqualArrays";
		};
	} // namespace typetraits

	namespace array {
		/// \brief Element-wise array addition
		///
		/// Performs element-wise addition on two arrays. They must both be the same size and of
		/// the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise sum of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto
		operator+(LHS &&lhs, RHS &&rhs) LIBRAPID_RELEASE_NOEXCEPT
		  ->detail::Function<typetraits::DescriptorType_t<LHS, RHS>, detail::Plus, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>, detail::Plus>(
			  std::forward<LHS>(lhs), std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array subtraction
		///
		/// Performs element-wise subtraction on two arrays. They must both be the same size and
		/// of the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise difference of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto
		operator-(LHS &&lhs, RHS &&rhs) LIBRAPID_RELEASE_NOEXCEPT
		  ->detail::Function<typetraits::DescriptorType_t<LHS, RHS>, detail::Minus, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>, detail::Minus>(
			  std::forward<LHS>(lhs), std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array multiplication
		///
		/// Performs element-wise multiplication on two arrays. They must both be the same size
		/// and of the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise product of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto
		operator*(LHS &&lhs, RHS &&rhs) LIBRAPID_RELEASE_NOEXCEPT
		  ->detail::Function<typetraits::DescriptorType_t<LHS, RHS>, detail::Multiply, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>, detail::Multiply>(
			  std::forward<LHS>(lhs), std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array division
		///
		/// Performs element-wise division on two arrays. They must both be the same size and of
		/// the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise division of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto
		operator/(LHS &&lhs, RHS &&rhs) LIBRAPID_RELEASE_NOEXCEPT
		  ->detail::Function<typetraits::DescriptorType_t<LHS, RHS>, detail::Divide, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>, detail::Divide>(
			  std::forward<LHS>(lhs), std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array comparison, checking whether a < b for all a, b in input
		/// arrays
		///
		/// Performs an element-wise comparison on two arrays, checking if the first value is
		/// less than the second. They must both be the same size and of the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise comparison of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto
		operator<(LHS &&lhs, RHS &&rhs) LIBRAPID_RELEASE_NOEXCEPT
		  ->detail::Function<typetraits::DescriptorType_t<LHS, RHS>, detail::LessThan, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>, detail::LessThan>(
			  std::forward<LHS>(lhs), std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array comparison, checking whether a > b for all a, b in input
		/// arrays
		///
		/// Performs an element-wise comparison on two arrays, checking if the first value is
		/// greater than the second. They must both be the same size and of the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise comparison of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto operator>(LHS &&lhs, RHS &&rhs)
		  LIBRAPID_RELEASE_NOEXCEPT->detail::Function<typetraits::DescriptorType_t<LHS, RHS>,
													  detail::GreaterThan, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>,
										detail::GreaterThan>(std::forward<LHS>(lhs),
															 std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array comparison, checking whether a <= b for all a, b in input
		/// arrays
		///
		/// Performs an element-wise comparison on two arrays, checking if the first value is
		/// less than or equal to the second. They must both be the same size and of the same
		/// data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise comparison of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto operator<=(LHS &&lhs, RHS &&rhs)
		  LIBRAPID_RELEASE_NOEXCEPT->detail::Function<typetraits::DescriptorType_t<LHS, RHS>,
													  detail::LessThanEqual, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>,
										detail::LessThanEqual>(std::forward<LHS>(lhs),
															   std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array comparison, checking whether a >= b for all a, b in input
		/// arrays
		///
		/// Performs an element-wise comparison on two arrays, checking if the first value is
		/// greater than or equal to the second. They must both be the same size and of the same
		/// data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise comparison of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto operator>=(LHS &&lhs, RHS &&rhs)
		  LIBRAPID_RELEASE_NOEXCEPT->detail::Function<typetraits::DescriptorType_t<LHS, RHS>,
													  detail::GreaterThanEqual, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>,
										detail::GreaterThanEqual>(std::forward<LHS>(lhs),
																  std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array comparison, checking whether a == b for all a, b in input
		/// arrays
		///
		/// Performs an element-wise comparison on two arrays, checking if the first value is
		/// equal to the second. They must both be the same size and of the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise comparison of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto operator==(LHS &&lhs, RHS &&rhs)
		  LIBRAPID_RELEASE_NOEXCEPT->detail::Function<typetraits::DescriptorType_t<LHS, RHS>,
													  detail::ElementWiseEqual, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>,
										detail::ElementWiseEqual>(std::forward<LHS>(lhs),
																  std::forward<RHS>(rhs));
		}

		/// \brief Element-wise array comparison, checking whether a != b for all a, b in input
		/// arrays
		///
		/// Performs an element-wise comparison on two arrays, checking if the first value is
		/// not equal to the second. They must both be the same size and of the same data type.
		///
		/// \tparam LHS Type of the LHS element
		/// \tparam RHS Type of the RHS element
		/// \param lhs The first array
		/// \param rhs The second array
		/// \return The element-wise comparison of the two arrays
		template<class LHS, class RHS>
		LIBRAPID_NODISCARD LIBRAPID_ALWAYS_INLINE auto operator!=(LHS &&lhs, RHS &&rhs)
		  LIBRAPID_RELEASE_NOEXCEPT->detail::Function<typetraits::DescriptorType_t<LHS, RHS>,
													  detail::ElementWiseNotEqual, LHS, RHS> {
			static_assert(
			  typetraits::IsSame<typename typetraits::TypeInfo<std::decay_t<LHS>>::Scalar,
								 typename typetraits::TypeInfo<std::decay_t<RHS>>::Scalar>,
			  "Operands must have the same data type");
			LIBRAPID_ASSERT(lhs.shape() == rhs.shape(), "Shapes must be equal");
			return detail::makeFunction<typetraits::DescriptorType_t<LHS, RHS>,
										detail::ElementWiseNotEqual>(std::forward<LHS>(lhs),
																	 std::forward<RHS>(rhs));
		}
	} // namespace array
} // namespace librapid

#endif // LIBRAPID_ARRAY_OPERATIONS_HPP