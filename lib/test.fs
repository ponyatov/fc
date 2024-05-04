module test

open NUnit.Framework

[<SetUp>]
let Setup () = ()

[<Test>]
let Test1 () = Assert.Pass()

// [<TestFixture>]
// type TestClass() =

//     [<Test>]
//     member this.Hello() = Assert.That(true, Is.True)

module Program =
    [<EntryPoint>]
    let main _ = 0
