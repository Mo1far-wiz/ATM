#pragma once

// [Interface] Require type to have an id
struct IId {
	virtual uint32_t GetId() const = 0;
};