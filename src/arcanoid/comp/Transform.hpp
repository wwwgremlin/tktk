/**
    tktk

    tktk - Copyright (C) 2015 Stanislav Demyanovich <stan@angrybubo.com>

    This software is provided 'as-is', without any express or
    implied warranty. In no event will the authors be held
    liable for any damages arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute
    it freely, subject to the following restrictions:

    1.  The origin of this software must not be misrepresented;
        you must not claim that you wrote the original software.
        If you use this software in a product, an acknowledgment
        in the product documentation would be appreciated but
        is not required.

    2.  Altered source versions must be plainly marked as such,
        and must not be misrepresented as being the original software.

    3.  This notice may not be removed or altered from any
        source distribution.
*/

#ifndef ARCANOID_COMP_TRANSFORM_HPP
#define ARCANOID_COMP_TRANSFORM_HPP

#include <tktk/ecs/ComponentBase.hpp>
#include <tktk/ecs/Processor.hpp>

#include <SFML/System.hpp>

using namespace tktk;

class Transform
: public ecs::ComponentBase
{
DECLARE_UNIQUE_COMP_TYPE

public:

    explicit Transform( ecs::Entity* owner );
    virtual ~Transform();

    sf::Vector2f& position() noexcept;
    const sf::Vector2f& position() const noexcept;

private:

    sf::Vector2f mPosition{ 0.0f, 0.0f };
};


class TransformProcessor
: public ecs::Processor<TransformProcessor, Transform>
{
public:

    TransformProcessor();
    virtual ~TransformProcessor();

    virtual void update( float deltaTime );
};

#endif /* end of include guard: ARCANOID_COMP_TRANSFORM_HPP */