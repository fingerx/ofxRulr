#pragma once

#include "../Utils/Set.h"

#include "../../../addons/ofxLiquidEvent/src/ofxLiquidEvent.h"

#include <string>
#include <memory>
#include <vector>

using namespace std;

namespace ofxDigitalEmulsion {
	namespace Graph {
		class BasePin {
		public:
			BasePin(string name);
			virtual string getTypeName() = 0;
			virtual string getNodeTypeName() = 0;
			string getName() const;
			virtual bool isConnected() const = 0;
		private:
			const string name;
		};

		template<typename NodeType>
		class Pin : public BasePin {
		public:
			Pin(string name) : BasePin(name) { }
			Pin() : BasePin(this->getNodeTypeName()) { }

			string getTypeName() override { return string("Pin::") + this->getNodeTypeName(); }
			string getNodeTypeName() override { return NodeType().getTypeName(); }
			void connect(shared_ptr<NodeType> node) {
				this->connection = node;
				this->onNewConnection(node);
			}
			shared_ptr<NodeType> getConnection() {
				return connection;
			}
			bool isConnected() const override {
				return (bool) this->connection;
			}
			
			ofxLiquidEvent<shared_ptr<NodeType> > onNewConnection;
		protected:
			shared_ptr<NodeType> connection;
		};

		typedef Utils::Set<BasePin> PinSet;
	}
}
