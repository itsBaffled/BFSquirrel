# BFSquirrel 🐿️

BFSquirrel is an Unreal Engine implementation of [squirrelnoise5](http://eiserloh.net/noise/SquirrelNoise5.hpp).

---

![Gif from Giphy](https://media.giphy.com/media/5UhoI8LK40iOppq8sR/giphy.gif)

The above gif demonstrates the two main node types:

- **`Squirrel Rand`** - A generic global random function (designed to replace `FMath::Rand()`).
- **`Squirrel Rand Stream`** - A struct with its own index and seed for confined randomness.

C++ implementations for global random functions can be found within the `Sqrl` namespace.

---

### `FSquirrelStream`

`FSquirrelStream` is a struct that has its own seed and index value, along with its own random functions. As you traverse and use your stream, you can also move backward and revisit previously generated random values by decrementing the stream's index instead of incrementing it. This is incredibly useful for deterministic pseudo-randomness.

#### Example Use Case: Shooting a Weapon

Consider a scenario where the server provides every client with a random seed. This allows clients to use their random values locally while maintaining synchronization without needing to replicate the newly generated value every time between all clients. As long as the seed remains in sync, the values will be consistent across all clients and the server (of course, if the seed goes out of sync, issues may arise).

#### Another Example: Shotgun Spread

If a client fires a shotgun and uses the `NextVectorInCone()` function on the stream (or any of them really), the client could send its seed and index to the server. The server can then recreate the exact random stream using the same `NextVectorInCone()` or even `PreviousVectorInCone()`, ensuring that the values remain identical between the client and the server, allowing for roll back or any other determinism.

---

As always, feel free to reach out if you have any questions or issues:
- [Twitter](https://twitter.com/itsBaffled)
