#pragma once

#include "Node.h"

#include "ofxCvGui/Panels/World.h"

namespace ofxDigitalEmulsion {
	namespace Graph {
		class Summary : public Node {
		public:
			Summary(const Utils::Set<Graph::Node> & world);
			string getTypeName() const override;
			ofxCvGui::PanelPtr getView() override;

			void update() override;

			void serialize(Json::Value &) override;
			void deserialize(const Json::Value &) override;
		protected:
			void populateInspector2(ofxCvGui::ElementGroupPtr);

			shared_ptr<ofxCvGui::Panels::World> view;

			ofParameter<bool> showCursor;
			ofParameter<bool> showGrid;

			const Utils::Set<Graph::Node> & world;
		};
	}
}