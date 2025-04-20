//#include "effect.h"
//#include "character.h"
//
//class Poison : public Effect {
//	public:
//		Poison(const int _damage, const int _duration) :
//			damage(_damage), duration(_duration) {};
//		void on_apply(Character& target) override {
//			//call log method
//		};
//		void on_turn_start(Character& target) override {
//			target.take_damage(damage);
//			duration--;
//			if (duration <= 0) {
//				on_remove(target);
//			}
//			//call log method
//		};
//		virtual void on_remove(Character& target) override {
//			//call log method
//		};
//		virtual bool is_expired() const override {
//			return duration <= 0;
//		};
//		virtual std::string get_name() const {
//			return "Poison";
//		};
//
//	private:
//		const int damage;
//		const int duration;
//};