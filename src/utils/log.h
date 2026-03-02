//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once

#include <memory>
#include "spdlog/spdlog.h"

class log {
public:
    static void Init();
    static void Close();

    static std::shared_ptr<spdlog::logger>& GetLogger() { return m_FP_logger; }

private:
    static std::shared_ptr<spdlog::logger> m_FP_logger;
};

#define FP_TRACE(fmt, ...)    ::log::GetLogger()->trace("- [ " fmt " ] -", ##__VA_ARGS__)
#define FP_DEBUG(fmt, ...)    ::log::GetLogger()->debug("- [ " fmt " ] -", ##__VA_ARGS__)
#define FP_INFO(fmt, ...)     ::log::GetLogger()->info("- [ " fmt " ] -", ##__VA_ARGS__)
#define FP_WARN(fmt, ...)     ::log::GetLogger()->warn("- [ " fmt " ] -", ##__VA_ARGS__)
#define FP_ERROR(fmt, ...)    ::log::GetLogger()->error("- [ " fmt " ] -", ##__VA_ARGS__)
#define FP_CRITICAL(fmt, ...) ::log::GetLogger()->critical("- [ " fmt " ] -", ##__VA_ARGS__)
