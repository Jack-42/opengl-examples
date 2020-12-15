#pragma once

#include <string>

#include "core/gl/OpenGLObject.hpp"

class Texture : public OpenGLObject
{
public:
    Texture(const std::string& filename);
    virtual ~Texture();

    virtual void bind() const override;
    virtual void unbind() const override;

    // TODO: other bind is overkill, remove superclass? probably superclass is overkill anyway
    void bindToSlot(unsigned int slot = 0) const;
private:
    unsigned int m_id;
};
