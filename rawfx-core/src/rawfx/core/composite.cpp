#include <rawfx/core/composite.h>

namespace rawfx {
namespace core {

void composite::on(const event& evt, engine& eng) {
    if (evt.is(ATTACH)) {
        _engine = &eng;
    }
    children.erase( std::remove_if(children.begin(), children.end(), [&evt, &eng](std::unique_ptr<handler>& h) {
        h->on(evt, eng);
        return eng.must_kill();
    }), children.end() );
}

composite* composite::add(handler* h) {
    children.push_back(std::unique_ptr<handler>(h));
    if (_engine != nullptr) {
        h->on(ATTACH, *_engine);
    }
    return this;
}

bool composite::empty() const {
    return children.empty();
}

}
}
