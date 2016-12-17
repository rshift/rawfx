#include <rawfx/core/composite.h>

namespace rawfx {
namespace core {

composite::~composite() {
    if (_engine != nullptr) {
        for (auto it = children.begin(); it != children.end(); it++) {
            (*it)->on(event(DETACH), *_engine);
        }
    }
}

void composite::on(const event& evt, engine& eng) {
    if (evt.is(ATTACH)) {
        _engine = &eng;
    }

    children.erase( std::remove_if(children.begin(), children.end(), [&evt, &eng](std::unique_ptr<handler>& h) {
        h->on(evt, eng);
        if (eng.must_kill()) {
            h->on(event(DETACH), eng);
            return true;
        }
        return false;
    }), children.end() );
    if (evt.is(DETACH)) {
        _engine = nullptr;
    }
}

void composite::add(handler* h) {
    children.push_back(std::unique_ptr<handler>(h));
    if (_engine != nullptr) {
        h->on(ATTACH, *_engine);
    }
}

bool composite::empty() const {
    return children.empty();
}

}
}
