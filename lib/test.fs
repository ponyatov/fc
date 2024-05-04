module test

open NUnit.Framework

[<SetUp>]
let Setup () = ()

[<Test>]
let pass () = Assert.Pass()

// [<Test>]
// let fail () = Assert.Fail

open fc

[<Test>]
let i123 () = Assert.AreEqual(Int 123, i123)

[<Test>]
let add12 () =
    Assert.AreEqual(add12, Op("+", Int 2, Int 3))

module Stub =
    [<EntryPoint>]
    let main _ = 0
