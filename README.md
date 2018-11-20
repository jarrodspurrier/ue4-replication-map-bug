# UE4 ReplicationMap Bug
Demonstrates a UE4 bug where `FObjectReplicator`s of `bSimulatedTask`s are not reused or removed from the `ReplicationMap` of non locally controlled characters resulting in a memory leak.

## Preparation:
1. Built with a source version of the Unreal Engine on 4.20.2.
2. Using Visual Studio 2017.
2. GameplayAbilities plugin was enabled.
3. An AbilitySystemComponent was added to the C++ generated character class.
4. A GameplayAbility Blueprint was created that simply runs the `ApplyRootMotionConstantForce` task then ends (this bug appears to occur on any `bSimulatedTask` as far as I'm concerned).
5. Created a timer on BeginPlay in the character's blueprint that activates the Ability every second.

## Repro Steps:
1. Start editor.
2. Enable `Run Dedicated Server`.
3. Set number of players to atleast `2`.
4. Play in editor.
5. Let it run for 10-20 seconds.
6. Set a breakpoint in `DataChannel.cpp` at line 3453 (make sure the Autos window is open: Debug > Windows > Autos).
7. Continue (F5) until you see a `ReplicationMap` where `Num` is greater than 2.
8. Examine its contents to see multiple `FObjectReplicator`s for the `AbilityTask_ApplyRootMotionConstantForce`.

A new `FObjectReplicator` is added to the `ReplicationMap` for every activation of the task and they never get removed. You can let the game run for however long and the `ReplicationMap` will grow indefinetly.

This behavior only occurs when the character activating the ability is not locally controlled. For instance, if you set the number of players back to 1 then perform the steps above, this will not occur and the `FObjectReplicator` for the task will be properly reused instead of having a new one created for every activation.

I have been able to reproduce this on every `bSimulatedTask`:
- AbilityTask_ApplyRootMotionConstantForce
- AbilityTask_ApplyRootMotionMoveToActorForce
- AbilityTask_ApplyRootMotionJumpForce
- AbilityTask_MoveToLocation
