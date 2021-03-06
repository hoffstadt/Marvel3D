#pragma once
#include <d3d11.h>
#include "mvBindable.h"
#include "mvComPtr.h"
#include "mvBufferResource.h"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
struct ID3D11DepthStencilView;

namespace Marvel {

	//-----------------------------------------------------------------------------
	// forward declarations
	//-----------------------------------------------------------------------------
	class mvGraphics;
	class mvRenderTarget;

	//-----------------------------------------------------------------------------
	// mvDepthStencil
	//-----------------------------------------------------------------------------
	class mvDepthStencil : public mvBindable, public mvBufferResource
	{

	public:

		enum class Usage{ DepthStencil, ShadowDepth};

		mvDepthStencil(mvGraphics& graphics, mvComPtr<ID3D11Texture2D> texture, UINT face);
		mvDepthStencil(mvGraphics& graphics, int width, int height, bool shaderBinding = false, Usage usage = Usage::DepthStencil);
		virtual ~mvDepthStencil() = default;

		// bindable interface
		void bind(mvGraphics& graphics) override {}

		// buffer resource interface
		void bindAsBuffer(mvGraphics& graphics) override;
		void bindAsBuffer(mvGraphics& graphics, mvBufferResource* renderTarget) override;
		void bindAsBuffer(mvGraphics& graphics, mvRenderTarget* renderTarget);
		void clear(mvGraphics& graphics) override;

		ID3D11DepthStencilView* getDepthStencilView();
		void reset();

	protected:

		mvComPtr<ID3D11DepthStencilView> m_DSV;

	};

	//-----------------------------------------------------------------------------
	// mvOutputDepthStencil
	//-----------------------------------------------------------------------------
	class mvOutputDepthStencil : public mvDepthStencil
	{

	public:

		mvOutputDepthStencil(mvGraphics& graphics, int width, int height);
		mvOutputDepthStencil(mvGraphics& graphics);
		mvOutputDepthStencil(mvGraphics& graphics, mvComPtr<ID3D11Texture2D> texture, UINT face);

		void bind(mvGraphics& graphics) override {}

	};

}