# 
# stack.rb by Ph. Jounin
#
# A link list using Ruby
# -------------------------------------------------
class Stack
    LinkedListItem = Struct.new( :data, :next )
    def initialize 
     @top = nil
    end
    def is_empty?
      @first.nil?
    end
    def push(data)
      @top = LinkedListItem.new(data, @top)
    end
    alias_method :"<<", :push
    def pop()
      if @top.nil? 
        nil
      else
        data = @top.data
        @top = @top.next
        data
      end
    end
end

myStack = Stack.new
myStack.push("bonjour")
myStack.push("les")
myStack.push("petits")
myStack.push("amis")
while  s=myStack.pop()
  puts s
end

