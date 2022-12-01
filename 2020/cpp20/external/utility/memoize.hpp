#ifndef UTILITY_MEMOIZE_HPP
#define UTILITY_MEMOIZE_HPP
#include <functional>
#include <map>
#include <tuple>
#include <type_traits>

namespace utility {

template <typename Signature, typename F, typename Projection>
class Memoize_helper;

template <typename R, typename... Args, typename F, typename Projection>
class Memoize_helper<R(Args...), F, Projection> {
   private:
    using Result_type   = R;
    using Function_type = F;
    using Args_tuple_type =
        std::tuple<std::decay_t<std::invoke_result_t<Projection, Args>>...>;

    Function_type f_;
    Projection projection_;
    mutable std::map<Args_tuple_type, Result_type> cache_;

   public:
    Memoize_helper(F&& f, Projection&& p) : f_(f), projection_{p} {}

    Memoize_helper(Memoize_helper const&) = delete;

   public:
    template <typename... Inner_args>
    auto operator()(Inner_args&&... args) const -> Result_type
    {
        auto const args_tuple = std::tuple{projection_(args)...};
        auto const cached     = cache_.find(args_tuple);

        if (cached != std::end(cache_))
            return cached->second;

        auto&& result      = f_(*this, std::forward<Inner_args>(args)...);
        cache_[args_tuple] = result;
        return result;
    }
};

/// Make a memoized version of \p f.
/** The signature of \p f should take a function as its first parameter, this
 *  will be a function object to the memoized version of itself. The Projection
 *  function is used on each argument to produce an identity for the memoized
 *  result to be looked up by. */
template <typename Signature, typename F, typename Projection = std::identity>
auto make_memoized(F&& f, Projection&& p = Projection{})
    -> Memoize_helper<Signature, std::decay_t<F>, Projection>
{
    return {std::forward<F>(f), std::forward<Projection>(p)};
}

}  // namespace utility
#endif  // UTILITY_MEMOIZE_HPP
