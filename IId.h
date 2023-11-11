#pragma once

// [Interface] Require type to have an id
struct IId {
	virtual size_t GetId() const = 0;
};