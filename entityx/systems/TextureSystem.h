#ifndef TEXTURESYSTEM_H
#define TEXTURESYSTEM_H

#include <map>
#include <entityx/entityx.h>
#include "keyvalues.h"
#include "entityx/events.h"
#include "entityx/components.h"
namespace ex = entityx;

/* The texture system takes the world entities (with Box2DLTBLComponent)
 * and draws textures over them. Handles random textures and management there.
 * Also draws the background texture */

class TextureSystem : public ex::System<TextureSystem>, public ex::Receiver<TextureSystem>
{
public:
    TextureSystem(sf::RenderWindow& rw, KeyValue& keys, ex::EntityManager& entities);

    //Updating is drawing textures all over the Box2D objects
    void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt) override;

    //Receiving events; this is coming from the GUI enabling/disable graphic freatures
    void configure(ex::EventManager& events) override;
    void receive(const GraphicsEvent& e);
    void receive(const ex::ComponentAddedEvent<SpawnComponent>& e);

private:
    //Reference to window to draw below textures to
    sf::RenderWindow& window;

    //Textures; Multiple are supported for boxes/balls.
    //`loadTextures` loads a colon-delimited list of textures into a vector
    //`texturemap` is a map of "type" -> {aviliable textures for type, Box2D scale factor}
    std::map<SpawnComponent::TYPE, std::pair<std::vector<sf::Texture>*,float>> texturemap;
    void loadTextures(std::vector<sf::Texture>&, const std::string&);
    std::vector<sf::Texture> boxTextures, ballTextures;
    sf::Texture bgTexture;

    //Figure out textures for an entity, and untextures entities
    void addToWorld(ex::Entity e);
    void retexture(ex::Entity e);
    void scaleTexture(ex::Entity e);
    sf::Sprite bgSprite;
    std::list<ex::Entity> unspawned;

    //State data. Passed from Graphics portion of GUI window
    bool imageRenderEnabled;
    bool randomTexturesEnabled;

private:
    //EntityX reference data, convience.
    ex::EntityManager& entities;
};

#endif // TEXTURESYSTEM_H
