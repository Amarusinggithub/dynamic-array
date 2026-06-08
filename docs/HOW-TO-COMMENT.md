# How to Comment Code

## The core rule

Comments should explain the **WHY**, not the **WHAT**. Well-named functions and variables already explain what the code does. A comment that just restates the code adds noise and rots as the code changes.

```c
// BAD — restates what the code already says
i++; // increment i

// GOOD — explains a non-obvious reason
i += 2; // skip null terminator, already counted in previous pass
```

---

## When to write a comment

### 1. Non-obvious algorithm choices

Code shows what is happening, not why this approach was chosen over another. If you picked one algorithm over alternatives, a reader might think the choice was arbitrary and "fix" it. A comment explaining the tradeoff — speed, distribution quality, memory use — protects a deliberate decision.

```c
// Polynomial rolling hash: better key distribution than simple sum,
// avoids collisions from anagrams ("abc" == "bca" with plain addition).
```

### 2. Invariants that must hold

An invariant is a condition that must be true at a specific point for the code to be correct. Nothing in a function signature can express that the caller must hold a lock, or that a buffer must be pre-initialized, or that two values must be kept in sync. The comment is the only contract you have.

```c
// Caller must acquire map_lock before calling this function.
void map_internal_insert(MapPtr map, NodePtr node);
```

### 3. Workarounds for specific bugs

Sometimes code looks wrong but is intentional — it compensates for a bug in hardware, a compiler, or an external library. Without a comment, the next developer sees something that looks redundant or strange and removes it, reintroducing a crash that took weeks to find the first time.

```c
// Flush pipeline here — Intel Core 2 errata #47:
// speculative reads can bypass store-release on this micro-architecture.
mb();
```

### 4. Subtle constraints not obvious from the types

C's type system is weak. A `void*` could be anything, a `size_t` could mean bytes, elements, or indices. When a parameter has a constraint the type cannot express, a comment is the only way to communicate it to the caller.

```c
// new_cap: number of buckets. Pass 0 to double the current capacity.
// Must be greater than map->length to avoid immediate resize on next put.
MAP_ERROR_CODES map_resize(MapPtr map, size_t new_cap);
```

---

## Where comments live

| Location                                    | Purpose                                                                                      |
| ------------------------------------------- | -------------------------------------------------------------------------------------------- |
| Header file (`@brief`, `@param`, `@return`) | Documents the public API for callers and doc generators (Doxygen)                            |
| Inside the `.c` implementation              | Only for the four cases above — non-obvious why, invariants, workarounds, subtle constraints |

---

## What not to comment

- Code that well-named identifiers already explain
- What a function does (the name and signature say that)
- References to the current task, ticket, or PR ("added for issue #42") — these belong in commit messages, not source code
- Anything that will obviously rot: commented-out old code, "TODO: fix this later" without a specific condition

---

## Production codebases

Well-written production code (Linux kernel, SQLite, LLVM) has **sparse, targeted comments** — not comments everywhere. What looks like "lots of comments" in unfamiliar codebases is usually:

- **Teaching/tutorial code** — explains everything for learners
- **Public library APIs** — doc comments for generated documentation
- **Legacy code** — compensates for cryptic variable names like `x`, `tmp2`, `flag`

The goal is that removing a comment would genuinely confuse a future reader. If it wouldn't, don't write it.
