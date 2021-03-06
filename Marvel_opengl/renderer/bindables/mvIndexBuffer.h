#pragma once
#include <vector>
#include <assert.h>
#include "mvBindable.h"
#include <GL/gl3w.h>

namespace Marvel
{
	class mvIndexBuffer : public mvBindable
	{

	public:

		mvIndexBuffer(mvGraphics& graphics, const std::vector<unsigned short>& indices);

		void bind  (mvGraphics& graphics) override;
		void unbind(mvGraphics& graphics) override;
		
		size_t getCount() const;

	private:

		GLuint       m_buffer;
		size_t       m_count = 0;

	};
}