#pragma once

// [Interface] Require type to have an id
struct IId {
	virtual uint32_t getId() const = 0;
};