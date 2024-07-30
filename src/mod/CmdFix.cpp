#include "mod/CmdFix.h"

#include <memory>

#include "ll/api/mod/RegisterHelper.h"

#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerJoinEvent.h"
#include "ll/api/service/Bedrock.h"
#include "mc/network/packet/AvailableCommandsPacket.h"
#include "mc/server/commands/CommandRegistry.h"


namespace cmd_fix {

static std::unique_ptr<CmdFix> instance;

CmdFix& CmdFix::getInstance() { return *instance; }

bool CmdFix::load() {
    getSelf().getLogger().info("Loading...");
    // Code for loading the plugin goes here.
    return true;
}

bool CmdFix::enable() {
    getSelf().getLogger().info("Enabling...");
    // Code for enabling the plugin goes here.
    ll::event::EventBus::getInstance().emplaceListener<ll::event::PlayerJoinEvent>([](ll::event::PlayerJoinEvent& event
                                                                                   ) {
        auto pkt = ll::service::getCommandRegistry()->serializeAvailableCommands();
        event.self().sendNetworkPacket(pkt);
    });
    return true;
}

bool CmdFix::disable() {
    getSelf().getLogger().info("Disabling...");
    // Code for disabling the plugin goes here.
    return true;
}

} // namespace cmd_fix

LL_REGISTER_MOD(cmd_fix::CmdFix, cmd_fix::instance);
