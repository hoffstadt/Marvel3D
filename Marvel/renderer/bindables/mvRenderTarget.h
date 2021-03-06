#pragma once
#include <d3d11.h>
#include "mvBindable.h"
#include "mvComPtr.h"
#include "mvDepthStencil.h"
#include "mvBufferResource.h"

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvGraphics;

	//-----------------------------------------------------------------------------
	// mvRenderTarget
	//-----------------------------------------------------------------------------
	class mvRenderTarget : public mvBindable, public mvBufferResource
	{

	public:

		mvRenderTarget(mvGraphics& graphics, int width, int height);
		mvRenderTarget(mvGraphics& graphics, ID3D11Texture2D* texture, int face = -1);

		// bindable interface
		void bind(mvGraphics& graphics) override {}

		// buffer resource interface
		void bindAsBuffer(mvGraphics& graphics) override;
		void bindAsBuffer(mvGraphics& graphics, mvBufferResource* depthStencilView) override;
		void clear(mvGraphics& graphics) override;

		void bindAsBuffer(mvGraphics& graphics, ID3D11DepthStencilView* depthStencilView);
		
		void reset();

		ID3D11RenderTargetView*   getTarget();
		mvComPtr<ID3D11RenderTargetView> getTargetCom();
		ID3D11ShaderResourceView* getShaderResource();

	private:

		UINT                               m_width;
		UINT                               m_height;
		mvComPtr<ID3D11RenderTargetView>   m_target;
		mvComPtr<ID3D11ShaderResourceView> m_shaderResource;

	};

}