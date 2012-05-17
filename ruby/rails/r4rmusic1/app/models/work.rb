class Work < ActiveRecord::Base
  # attr_accessible :title, :body
  belongs_to :composer
  has_many :editions
end
