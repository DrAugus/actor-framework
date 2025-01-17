// This file is part of CAF, the C++ Actor Framework. See the file LICENSE in
// the main distribution directory for license terms and copyright or visit
// https://github.com/actor-framework/actor-framework/blob/master/LICENSE.

#define CAF_SUITE typed_actor_view

#include "caf/typed_actor_view.hpp"

#include "core-test.hpp"

#include "caf/scheduled_actor/flow.hpp"
#include "caf/typed_actor.hpp"

using namespace caf;
using namespace std::literals;

namespace {

using shared_int = std::shared_ptr<int>;

using shared_err = std::shared_ptr<error>;

using int_actor = typed_actor<result<void>(int)>;

using int_actor_ptr = int_actor::pointer_view;

struct int_actor_state {
  using init_fn = std::function<void(int_actor_ptr)>;

  int_actor_state(int_actor_ptr ptr, init_fn fn)
    : self(ptr), init(std::move(fn)) {
    // nop
  }

  int_actor::behavior_type make_behavior() {
    init(self);
    return {
      [](int) {},
    };
  }

  int_actor_ptr self;
  init_fn init;
};

using int_actor_impl = int_actor::stateful_impl<int_actor_state>;

void stream_observer(event_based_actor* self, stream str, shared_int res,
                     shared_err err) {
  // Access `self` through the view to check correct forwarding of `observe_as`.
  auto view = typed_actor_view<result<void>(int)>{self};
  view.observe_as<int>(str, 30, 10)
    .do_on_error([err](const error& what) { *err = what; })
    .for_each([res](int value) { *res += value; });
}

void typed_stream_observer(event_based_actor* self, typed_stream<int> str,
                           shared_int res, shared_err err) {
  // Access `self` through the view to check correct forwarding of `observe`.
  auto view = typed_actor_view<result<void>(int)>{self};
  view.observe(str, 30, 10)
    .do_on_error([err](const error& what) { *err = what; })
    .for_each([res](int value) { *res += value; });
}

struct fixture : test_coordinator_fixture<> {
  int_actor spawn_int_actor(int_actor_state::init_fn init) {
    return sys.spawn<int_actor_impl>(std::move(init));
  }
};

} // namespace

BEGIN_FIXTURE_SCOPE(fixture)

SCENARIO("typed actors may use the flow API") {
  GIVEN("a typed actor") {
    WHEN("the actor calls make_observable") {
      THEN("the function returns a flow that lives on the typed actor") {
        auto res = std::make_shared<int>(0);
        spawn_int_actor([=](int_actor_ptr self) {
          self
            ->make_observable() //
            .iota(1)
            .take(10)
            .for_each([res](int value) { *res += value; });
        });
        run();
        CHECK_EQ(*res, 55);
      }
    }
    WHEN("the actor creates a stream via compose") {
      THEN("other actors may observe the values") {
        auto res = std::make_shared<int>(0);
        auto err = std::make_shared<error>();
        spawn_int_actor([=](int_actor_ptr self) {
          auto str = self
                       ->make_observable() //
                       .iota(1)
                       .take(10)
                       .compose(self->to_stream("foo", 10ms, 10));
          self->spawn(stream_observer, str, res, err);
        });
        run();
        CHECK_EQ(*res, 55);
        CHECK_EQ(*err, sec::none);
      }
    }
    WHEN("the actor creates a stream via to_stream") {
      THEN("other actors may observe the values") {
        auto res = std::make_shared<int>(0);
        auto err = std::make_shared<error>();
        spawn_int_actor([=](int_actor_ptr self) {
          auto obs = self
                       ->make_observable() //
                       .iota(1)
                       .take(10)
                       .as_observable();
          auto str = self->to_stream("foo", 10ms, 10, obs);
          self->spawn(stream_observer, str, res, err);
        });
        run();
        CHECK_EQ(*res, 55);
        CHECK(!*err);
      }
    }
    WHEN("the actor creates a typed stream via compose") {
      THEN("other actors may observe the values") {
        auto res = std::make_shared<int>(0);
        auto err = std::make_shared<error>();
        spawn_int_actor([=](int_actor_ptr self) {
          auto str = self
                       ->make_observable() //
                       .iota(1)
                       .take(10)
                       .compose(self->to_typed_stream("foo", 10ms, 10));
          self->spawn(typed_stream_observer, str, res, err);
        });
        run();
        CHECK_EQ(*res, 55);
        CHECK(!*err);
      }
    }
    WHEN("the actor creates a typed stream via to_typed_stream") {
      THEN("other actors may observe the values") {
        auto res = std::make_shared<int>(0);
        auto err = std::make_shared<error>();
        spawn_int_actor([=](int_actor_ptr self) {
          auto obs = self
                       ->make_observable() //
                       .iota(1)
                       .take(10)
                       .as_observable();
          auto str = self->to_typed_stream("foo", 10ms, 10, obs);
          self->spawn(typed_stream_observer, str, res, err);
        });
        run();
        CHECK_EQ(*res, 55);
        CHECK(!*err);
      }
    }
  }
  WHEN("the actor creates a stream and deregisters it immediately") {
    THEN("other actors receive an error when observing the stream") {
      auto res = std::make_shared<int>(0);
      auto err = std::make_shared<error>();
      spawn_int_actor([=](int_actor_ptr self) {
        auto str = self
                     ->make_observable() //
                     .iota(1)
                     .take(10)
                     .compose(self->to_stream("foo", 10ms, 10));
        self->spawn(stream_observer, str, res, err);
        self->deregister_stream(str.id());
      });
      run();
      CHECK_EQ(*res, 0);
      CHECK_EQ(*err, sec::invalid_stream);
    }
  }
}

END_FIXTURE_SCOPE()
