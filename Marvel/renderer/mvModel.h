#pragma once
#include "mvGraphics.h"
#include <string>
#include <vector>
#include <memory>
#include "mvNode.h"
#include "mvMesh.h"
#include "mvGizmo.h"
#include "mvObjMaterial.h"

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvBaseRenderGraph;
	class mvModelProbe;

	//-----------------------------------------------------------------------------
	// mvModel
	//-----------------------------------------------------------------------------
	class mvModel
	{

	public:

		mvModel(mvGraphics& graphics, const std::string& pathString, float scale = 1.0f);

		// propagates through graph linking steps to passes
		// model -> node -> mesh -> step -> pass
		void linkSteps(mvBaseRenderGraph& graph);

		// propagates through graph submitting jobs
		// model -> node -> mesh -> step -> pass
		void submit(mvBaseRenderGraph& graph) const;

		// sets the root transform which will propagate
		// through the graph
		void setRootTransform(glm::mat4 tf);

		void     accept          (mvModelProbe& probe);
		mvNode*  getNode         (const std::string& name);
		mvGizmo& getGizmo        () { return m_mesh; }

	private:

		mvNode* parseNode(mvGraphics& graphics, mvObjParser& parser, mvObjMaterialParser& mat, const std::string& pathString, int& id, const mvObjNode& node, float scale);

	private:

		std::shared_ptr<mvNode>              m_root;
		std::vector<std::shared_ptr<mvMesh>> m_meshes;
		mvGizmo                              m_mesh;
	};
}