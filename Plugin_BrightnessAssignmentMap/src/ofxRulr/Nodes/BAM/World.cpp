#include "pch_Plugin_BrightnessAssignmentMap.h"
#include "HistogramWidget.h"

namespace ofxRulr {
	namespace Nodes {
		namespace BAM {
			//----------
			World::World() {
				RULR_NODE_INIT_LISTENER;
			}

			//----------
			std::string World::getTypeName() const {
				return "BAM::World";
			}

			//----------
			void World::init() {
				RULR_NODE_INSPECTOR_LISTENER;

				this->addInput<Nodes::Base>("Scene");
				this->manageParameters(this->parameters);
			}

			//----------
			void World::populateInspector(ofxCvGui::InspectArguments & inspectArgs) {
				auto inspector = inspectArgs.inspector;

				auto histogramWidget = make_shared<HistogramWidget>();
				auto histogramWidgetWeak = weak_ptr<HistogramWidget>(histogramWidget);
				auto updateHistogram = [this, histogramWidgetWeak]() {
					auto histogramWidget = histogramWidgetWeak.lock();
					if (histogramWidget) {
						cv::Mat histogram;
						auto projectors = this->getProjectors();
						for (auto projector : projectors) {
							auto & bamPass = projector->getPass(Pass::Level::BrightnessAssignmentMap, true);
							histogram = bamPass.getHistogram(histogram);
						}
						histogramWidget->setData(histogram);
					}
				};
				//updateHistogram();
				inspector->add(histogramWidget);

				inspector->addButton("Update histogram", updateHistogram);
			}

			//----------
			void World::registerProjector(shared_ptr<Projector> projector) {
				this->projectors.emplace_back(projector);
			}

			//----------
			void World::unregisterProjector(shared_ptr<Projector> projector) {
				for (auto it = this->projectors.begin(); it != this->projectors.end();) {
					auto otherProjector = it->lock();
					if (!otherProjector || otherProjector == projector) {
						it = this->projectors.erase(it);
					}
					else {
						++it;
					}
				}
			}

			//----------
			vector<shared_ptr<Projector>> World::getProjectors() const {
				//return only active projectors

				vector<shared_ptr<Projector>> projectors;
				for (auto projectorWeak : this->projectors) {
					auto projector = projectorWeak.lock();
					if (projector) {
						projectors.emplace_back(projector);
					}
				}
				return projectors;
			}

			//----------
			const ofParameterGroup & World::getParameters() const {
				return this->parameters;
			}
		}
	}
}