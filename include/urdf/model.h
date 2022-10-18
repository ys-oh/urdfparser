#ifndef URDF_MODEL_H
#define URDF_MODEL_H

#include <string>
#include <map>

#include "urdf/common.h"
#include "urdf/exception.h"
#include "urdf/link.h"
#include "urdf/joint.h"

namespace urdf {

	struct UrdfModel {
		std::string name;
		std::shared_ptr<Link> root_link;

		std::map<std::string, std::shared_ptr<Link>> link_map;
		std::map<std::string, std::shared_ptr<Joint>> joint_map;
		std::map<std::string, std::shared_ptr<Material>> material_map;

		const std::string& getName() const { return name; }
		std::shared_ptr<Link> getRoot() const { return root_link; }

		std::shared_ptr<Link> getLink(const std::string& name);
		std::shared_ptr<Joint> getJoint(const std::string& name);
		std::shared_ptr<Material> getMaterial(const std::string& name);

		void getLinks(std::vector<std::shared_ptr<Link>>& linklist) const;

		void clear() {
			name.clear();

			link_map.clear();

			joint_map.clear();

			material_map.clear();

			root_link = nullptr;
		};


		void initLinkTree(std::map<std::string, std::string>& parent_link_tree);
		void findRoot(const std::map<std::string, std::string> &parent_link_tree);

		UrdfModel() { clear(); }

		static std::shared_ptr<UrdfModel> fromUrdfStr(const std::string& xml_string);
	};

}

#endif
