#ifndef OPTIONAL
// TODO: implement ***::insert with optional, instead of pair
namespace rider::faiz
{
	// `faiz::nullopt_t` is an empty class type used to indicate optional type
	// with uninitialized state. In particular, `faiz::optional` has a
	// constructor with nullopt_t as a single argument, which creates an
	// optional that does not contain a value.
	//
	// faiz::nullopt_t must be a non-aggregate LiteralType and cannot have a
	// default constructor or an initializer-list constructor.
	//
	// It must have a constexpr constructor that takes some
	// implementation-defined literal type.
	//
	// The constraints on nullopt_t's constructors exist to support both `op =
	// {};` and `op = nullopt;` as the syntax for disengaging an optional
	// object.
	struct nullopt_t
	{
		struct secret_tag
		{
			inline explicit secret_tag() = default;
		};
		constexpr explicit nullopt_t(secret_tag, secret_tag) noexcept
		{}
	};

	// `faiz::nullopt` is a constant of type `faiz::nullopt_t` that is used to
	// indicate optional type with uninitialized state.
	inline constexpr nullopt_t nullopt{
		nullopt_t::secret_tag{}, nullopt_t::secret_tag{}};

} // namespace rider::faiz
#	define OPTIONAL
#endif