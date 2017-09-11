
#pragma once

#define FSM_VERSION "1.0.0" 

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace fsm
{
    typedef std::function< void(const  void * args ) > call;
	/*״̬*/
    struct state {
        int name;
        const void * args;

        state( const int &name = 'null' ) : name(name)
        {}

        state operator()() const {
            state self = *this;
            self.args = NULL;
            return self;
        }

        state operator()( const void * t0 ) const {
            state self = *this;
            self.args = t0;
            return self;
        }
      

        operator int () const {
            return name;
        }

        bool operator<( const state &other ) const {
            return name < other.name;
        }
        bool operator==( const state &other ) const {
            return name == other.name;
        }

        
    };

    typedef state trigger;

    struct transition {
        fsm::state previous, trigger, current;

        template<typename ostream>
        inline friend ostream &operator<<( ostream &out, const transition &t ) {
            out << t.previous << " -> " << t.trigger << " -> " << t.current;
            return out;
        }
    };

    class stack {
    public:

        stack( const fsm::state &start = 'null' ) : deque(1) {
            deque[0] = start;
            call( deque.back(), 'init' );
        }

        stack( int start ) : stack( fsm::state(start) ) 
        {}

        ~stack() {
            // ensure state destructors are called (w/ 'quit')
            while( size() ) {
                pop();
            }
        }

        // pause current state (w/ 'push') and create a new active child (w/ 'init')
        void push( const fsm::state &state ) {
            if( deque.size() && deque.back() == state ) {
                return;
            }
            // queue
            call( deque.back(), 'push' );
            deque.push_back( state );
            call( deque.back(), 'init' );
        }

        // terminate current state and return to parent (if any)
        void pop() {
            if( deque.size() ) {
                call( deque.back(), 'quit' );
                deque.pop_back();
            }
            if( deque.size() ) {
                call( deque.back(), 'back' );
            }
        }

        // set current active state
        void set( const fsm::state &state ) {
            if( deque.size() ) {
                replace( deque.back(), state );
            } else {
                push(state);
            }
        }

        // number of children (stack)
        size_t size() const {
            return deque.size();
        }

        fsm::state get_state( signed pos = -1 ) const {
            signed size = (signed)(deque.size());
            return size ? *( deque.begin() + (pos >= 0 ? pos % size : size - 1 + ((pos+1) % size) ) ) : fsm::state();
        }
        fsm::transition get_log( signed pos = -1 ) const {
            signed size = (signed)(log.size());
            return size ? *( log.begin() + (pos >= 0 ? pos % size : size - 1 + ((pos+1) % size) ) ) : fsm::transition();
        }
		fsm::state get_trigger() const {
            return current_trigger;
        }

        bool is_state( const fsm::state &state ) const {
            return deque.empty() ? false : ( deque.back() == state );
        }

        // setup
        fsm::call &on( const fsm::state &from, const fsm::state &to ) {
            return callbacks[ bistate(from,to) ];
        }

        // generic call
        bool call( const fsm::state &from, const fsm::state &to ) const {
            std::map< bistate, fsm::call >::const_iterator found = callbacks.find(bistate(from,to));
            if( found != callbacks.end() ) {
                log.push_back( { from, current_trigger, to } );
                if( log.size() > 50 ) {
                    log.pop_front();
                }
                found->second( to.args );
                return true;
            }
            return false;
        }

        // user commands
        bool command( const fsm::state &trigger ) {
            size_t size = this->size();
            if( !size ) {
                return false;
            }
            current_trigger = fsm::state();
            std::deque< states::reverse_iterator > aborted;
            for( auto it = deque.rbegin(); it != deque.rend(); ++it ) {
                fsm::state &self = *it;
                if( !call(self,trigger) ) {
                    aborted.push_back(it);
                    continue;
                }
                for( auto it = aborted.begin(), end = aborted.end(); it != end; ++it ) {
                    call(**it, 'quit');
                    deque.erase(--(it->base()));
                }
                current_trigger = trigger;
                return true;
            }
            return false;
        }
        bool command( const fsm::state &trigger, const void *arg1 ) {
            return command( trigger(arg1) );
        }
    protected:

        void replace( fsm::state &current, const fsm::state &next ) {
            call( current, 'quit' );
            current = next;
            call( current, 'init' );
        }

        typedef std::pair<int, int> bistate;
        std::map< bistate, fsm::call > callbacks;

        mutable std::deque< fsm::transition > log;
        std::deque< fsm::state > deque;
        fsm::state current_trigger;

        typedef std::deque< fsm::state > states;
    };
}

